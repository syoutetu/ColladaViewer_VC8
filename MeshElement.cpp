#include "stdafx.h"

#include "MeshElement.h"



MeshElement::MeshElement()
{
	elemVertices = NULL;
}


MeshElement::~MeshElement()
{
	SAFE_DELETE(elemVertices);

	ClearVector(vecElemSource);
	ClearVector(vecElemLines);
	ClearVector(vecElemLinestrips);
	ClearVector(vecElemPolygons);
	ClearVector(vecElemTriangles);
	ClearVector(vecElemTrifans);
	ClearVector(vecElemTristrips);
}



void MeshElement::ReadNode(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	ReadAttributes( node );

	DOMNode* currentNode = node->getFirstChild();
	while( currentNode != NULL )
	{
#if _DEBUG	// デバッグ時に名前をチェックする為に
		const XMLCh* name = currentNode->getNodeName();
#endif

		if( IsElementNode( currentNode ) )
		{
			if( Is_source_NodeName( currentNode ) )
			{
				SourceElement* elemSource = new SourceElement();

				elemSource->ReadNode( currentNode );
				vecElemSource.push_back( elemSource );
			}
			else if( Is_vertices_NodeName( currentNode ) )
			{
				_ASSERTE(elemVertices == NULL);		// 必ず1つ存在するのでこの時点ではNULL
				elemVertices = new VerticesElement();

				elemVertices->ReadNode( currentNode );
			}
			else if( Is_lines_NodeName( currentNode ) )
			{
				LinesElement* elemLines = new LinesElement();

				elemLines->ReadNode( currentNode );
				vecElemLines.push_back( elemLines );
			}
			else if( Is_linestrips_NodeName( currentNode ) )
			{
				LinestripsElement* elemLinestrips = new LinestripsElement();

				elemLinestrips->ReadNode( currentNode );
				vecElemLinestrips.push_back( elemLinestrips );
			}
			else if( Is_polygons_NodeName( currentNode ) )
			{
				PolygonsElement* elemPolygons = new PolygonsElement();

				elemPolygons->ReadNode( currentNode );
				vecElemPolygons.push_back( elemPolygons );
			}
			else if( Is_triangles_NodeName( currentNode ) )
			{
				TrianglesElement* elemTriangles = new TrianglesElement();

				elemTriangles->ReadNode( currentNode );
				vecElemTriangles.push_back( elemTriangles );
			}
			else if( Is_trifans_NodeName( currentNode ) )
			{
				TrifansElement* elemTrifans = new TrifansElement();

				elemTrifans->ReadNode( currentNode );
				vecElemTrifans.push_back( elemTrifans );
			}
			else if( Is_tristrips_NodeName( currentNode ) )
			{
				TristripsElement* elemTristrips = new TristripsElement();

				elemTristrips->ReadNode( currentNode );
				vecElemTristrips.push_back( elemTristrips );
			}
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}


bool MeshElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemSource.empty() ) { str += L"<source>要素が存在しません\n"; }

	if( elemVertices != NULL ) { elemVertices->ValidElements( str ); }
	else { str += L"<vertices>要素が存在しません\n"; }

	ValidElementsInContainer( vecElemSource, str );
	ValidElementsInContainer( vecElemLines, str );
	ValidElementsInContainer( vecElemLinestrips, str );
	ValidElementsInContainer( vecElemPolygons, str );
	ValidElementsInContainer( vecElemTriangles, str );
	ValidElementsInContainer( vecElemTrifans, str );
	ValidElementsInContainer( vecElemTristrips, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<mesh>\n" + str;
	}

	return str.empty();
}


SourceElement* MeshElement::GetSourceElementById(const std::wstring& id) const	// wstringはあえて参照にしていない
{
	for( VECSOURCEELEM::const_iterator it = vecElemSource.begin(); it != vecElemSource.end(); ++it )
	{
		if( id.empty() ) { continue; }

		unsigned int offset = (id[0] == L'#' ? 1 : 0);	// 最初の文字が'#'の場合は次の文字から
		const std::wstring& sourceId = (*it)->GetIdAttribute();

		if( id.compare( offset, sourceId.length(), sourceId ) == 0 )
		{
			return *it;
		}
	}

	return NULL;
}



void MeshElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
}


// elemPrimのindex要素を出現した順番で取得する
// includeVerticesがtrueの場合はvertices要素への参照も含める
void MeshElement::GetAllInputElement(const BasePrimitive* elemPrim, VECINPUTELEM& vecInput, bool includeVertices) const
{
	for( unsigned int i = 0; i < elemPrim->GetInputCount(); i++ )
	{
		InputElement* elemInput = elemPrim->GetInputElement( i );

		if( includeVertices && IsVerticesElementReference( elemInput ) )
		{
			if( elemVertices == NULL ) { continue; }
			for( unsigned int j = 0; j < elemVertices->GetInputCount(); j++ )
			{
				vecInput.push_back( elemVertices->GetInputElement( j ) );
			}
		}
		else
		{
			vecInput.push_back( elemInput );
		}
	}
}



// メッシュデータをトライアングルリストで取得する
// 失敗した場合はfalseを返す
// vertexDataにはInput要素の出現によって、法線、テクスチャ座標などが含まれる場合がある
// vertexDataは呼び出した側でdelete[]しなければならない
bool MeshElement::CreateTriangleList(unsigned int& vertexCount, float*& vertexData, PRIM_TYPE primType, unsigned int primIndex) const
{
	switch( primType )
	{
	case PRIM_TYPE_POLYGONS:
		return CreateTriangleListFromPolygons( vertexCount, vertexData, primIndex );

	case PRIM_TYPE_TRIANGLES:
		return CreateTriangleListFromTriangles( vertexCount, vertexData, primIndex );

	case PRIM_TYPE_TRIFANS:
		return CreateTriangleListFromTrifans( vertexCount, vertexData, primIndex );

	case PRIM_TYPE_TRISTRIPS:
		return CreateTriangleListFromTristrips( vertexCount, vertexData, primIndex );

	case PRIM_TYPE_LINES:
		_ASSERTE(!"Lines Primitive Unsupported");
		return false;	// 未実装

	case PRIM_TYPE_LINESTRIPS:
		_ASSERTE(!"Linestrips Primitive Unsupported");
		return false;	// 未実装
	}
	
	_ASSERTE(!"Unknown Primitive Type");
	return false;
}


// オーバーロード
// 最初に見つかったプリミティブデータをトライアングルリストに変換する
bool MeshElement::CreateTriangleList(unsigned int& vertexCount, float*& vertexData) const
{
	vertexCount = 0;
	vertexData = NULL;

	if( GetPolygonsCount() > 0 )	{ return CreateTriangleList( vertexCount, vertexData, PRIM_TYPE_POLYGONS, 0 ); }
	if( GetTrianglesCount() > 0 )	{ return CreateTriangleList( vertexCount, vertexData, PRIM_TYPE_TRIANGLES, 0 ); }
	if( GetTrifansCount() > 0 )		{ return CreateTriangleList( vertexCount, vertexData, PRIM_TYPE_TRIFANS, 0 ); }
	if( GetTristripsCount() > 0 )	{ return CreateTriangleList( vertexCount, vertexData, PRIM_TYPE_TRISTRIPS, 0 ); }
	if( GetLinesCount() > 0 )		{ return CreateTriangleList( vertexCount, vertexData, PRIM_TYPE_LINES, 0 ); }
	if( GetLinestripsCount() > 0 )	{ return CreateTriangleList( vertexCount, vertexData, PRIM_TYPE_LINESTRIPS, 0 ); }

	_ASSERTE(!"No Primitive Data");
	return false;
}



// vertices要素を参照している場合はtrueを返す
bool MeshElement::IsVerticesElementReference(const InputElement* elemInput) const
{
	if( elemInput == NULL ) { return false; }
	return IsVerticesElementReference( elemInput->GetSourceAttribute() );
}

bool MeshElement::IsVerticesElementReference(const std::wstring& id) const
{
	_ASSERTE(elemVertices != NULL);

	if( elemVertices == NULL ) { return false; }
	if( id.empty() ) { return false; }

	unsigned int offset = (id[0] == L'#' ? 1 : 0);	// 最初の文字が'#'の場合は次の文字から
	const std::wstring& verticesId = elemVertices->GetIdAttribute();

	return id.compare( offset, verticesId.length(), verticesId ) == 0;
}


unsigned int MeshElement::GetCommonTechniqueAccessorStride(const SourceElement* elemSource) const
{
	_ASSERTE(elemSource != NULL);

	// profile属性がCOMMONのtechnique要素を取得する
	TechniqueElement* elemTech = elemSource->GetTechniqueOfCommonProfile();
	if( elemTech == NULL ) { _ASSERTE(!"COMMON Technique Element Not Found"); return 0; }

	unsigned int stride = 0;

	// すべてのaccessor要素のstride属性の和を取得する
	for( unsigned int j = 0; j < elemTech->GetAccessorCount(); j++ )
	{
		stride += elemTech->GetAccessorElement( j )->GetStrideAttribure();
	}

	return stride;
}


// input要素のidx属性の順にsource要素とinput要素が参照しているsource要素の数を取得する
bool MeshElement::FindInputSource(const BasePrimitive* elemPrim, VECUINT& vecSourceCount, VECSOURCEELEM& vecSource, unsigned int& vertexStride) const
{
	vertexStride = 0;

	VECINPUTELEM vecInput;

	// すべてのinput要素を取得する
	for( unsigned int i = 0; i < elemPrim->GetInputCount(); i++ )
	{
		InputElement* elemInput = elemPrim->GetInputElementByAttrIdx( i );
		_ASSERTE(elemInput != NULL);

		unsigned int sourceCount = 0;

		if( IsVerticesElementReference( elemInput ) )	// vertices要素を参照している場合
		{
			for( unsigned int j = 0; j < elemVertices->GetInputCount(); j++ )
			{
				vecInput.push_back( elemVertices->GetInputElement( j ) );
				sourceCount++;
			}
		}
		else
		{
			vecInput.push_back( elemInput );
			sourceCount++;
		}

		vecSourceCount.push_back( sourceCount );
	}

	// すべてのsource要素を取得する
	for( VECINPUTELEM::iterator it = vecInput.begin(); it != vecInput.end(); ++it )
	{
		SourceElement* elemSource = GetSourceElementById( (*it)->GetSourceAttribute() );
		if( elemSource == NULL ) { _ASSERTE(!"Reference Of Source Element Not Found"); return false; }
		
		unsigned int stride = GetCommonTechniqueAccessorStride( elemSource );
		
		if( stride > 0 )
		{
			vertexStride += stride;
			vecSource.push_back( elemSource );
		}
	}

	return true;
}



// polygons要素のデータをトライアングルリストに変換する
bool MeshElement::CreateTriangleListFromPolygons(unsigned int& vertexCount, float*& vertexData, unsigned int primIndex) const
{
	vertexCount = 0;
	vertexData = NULL;

	if( primIndex >= GetPolygonsCount() ) { return false; }
	PolygonsElement* elemPolygons = GetPolygonsElement( primIndex );
	
	unsigned int vertexStride = 0;	// 頂点データのサイズを保存する
	// すべてのinput要素から参照されているsource要素とその数を取得する:
	VECUINT vecSourceCount;
	VECSOURCEELEM vecSource;
	FindInputSource( elemPolygons, vecSourceCount, vecSource, vertexStride );

	const unsigned int inputCount = elemPolygons->GetInputCount();

	// トライアングルリストに変換したときの頂点の数を計算する
	for( unsigned int i = 0; i < elemPolygons->GetPrimitiveCount(); i++ )
	{
		PrimitiveElement * elemP = elemPolygons->GetPrimitiveElement( i );
		_ASSERTE(elemP->GetCount() / inputCount >= 3);	// 3つ以上でなければトライアングルにならない
		vertexCount += (elemP->GetCount() / inputCount - 2) * 3;	
	}

	// メモリを確保して頂点データをコピーする:
	vertexData = new float[vertexStride * vertexCount];

	float* vertexPointer = vertexData;

	for( unsigned int i = 0; i < elemPolygons->GetPrimitiveCount(); i++ )
	{
		PrimitiveElement* elemP = elemPolygons->GetPrimitiveElement( i );
		unsigned int triangleCount = elemP->GetCount() / inputCount;

		// トライアングル単位の頂点データをコピーする(とりあえずTRIFANSと同じように処理する)
		for( unsigned int j = 2; j < triangleCount; j++ )
		{
			float* triangle = vertexPointer;
			unsigned int sourceIndex = 0;	// source要素配列のインデックス(inputがverticesを参照する場合があるので)

			_ASSERTE(inputCount == (unsigned int)vecSourceCount.size());		// input要素の数と同じ
			for( unsigned int k = 0; k < inputCount; k++ )	// プリミティブのinput要素の数
			{
				unsigned int index0 = elemP->GetValue( k );		// 最初のインデックス
				unsigned int index1 = elemP->GetValue( (j - 1) * inputCount + k );	// 1つ前のインデックス
				unsigned int index2 = elemP->GetValue( j * inputCount + k );	// 現在のインデックス

				for( unsigned int s = 0; s < vecSourceCount[k]; s++ )	// inputが参照するsource要素の数
				{
					SourceElement* elemSource = vecSource[sourceIndex++];

					TechniqueElement* elemTech = elemSource->GetTechniqueOfCommonProfile();
					if( elemTech == NULL ) { _ASSERTE(!"Not Found COMMON Technique"); continue; }

					for( unsigned int a = 0; a < elemTech->GetAccessorCount(); a++ )	// accessor要素の数
					{
						AccessorElement* elemAccessor = elemTech->GetAccessorElement( a );
						unsigned int stride = elemAccessor->GetStrideAttribure();
						FloatArrayElement* elemFloatArray = elemSource->GetFloatArrayElement( elemAccessor );
						if( elemFloatArray == NULL ) { _ASSERTE(!"Not Found Float Array"); continue; }

						for( unsigned int t = 0; t < stride; t++ )
						{
							triangle[vertexStride * 0 + t] = elemFloatArray->GetValue( index0 * stride + t );
							triangle[vertexStride * 1 + t] = elemFloatArray->GetValue( index1 * stride + t );
							triangle[vertexStride * 2 + t] = elemFloatArray->GetValue( index2 * stride + t );
						}

						triangle += stride;
					}
				}
			}

			vertexPointer += vertexStride * 3;
		}
	}

	return true;
}


// triangles要素のデータをトライアングルリストに変換する
bool MeshElement::CreateTriangleListFromTriangles(unsigned int& vertexCount, float*& vertexData, unsigned int index) const
{
	_ASSERTE(!"This Method Has Not Tested");		// まだ実際のデータでテストしていない


	return true;
}


// trifans要素のデータをトライアングルリストに変換する
bool MeshElement::CreateTriangleListFromTrifans(unsigned int& vertexCount, float*& vertexData, unsigned int index) const
{	
	_ASSERTE(!"This Method Has Not Tested");		// まだ実際のデータでテストしていない


	return true;
}


// tristrips要素のデータをトライアングルリストに変換する
bool MeshElement::CreateTriangleListFromTristrips(unsigned int& vertexCount, float*& vertexData, unsigned int index) const
{	
	_ASSERTE(!"This Method Has Not Tested");		// まだ実際のデータでテストしていない


	return true;
}


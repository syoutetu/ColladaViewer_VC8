#include "stdafx.h"

#include "SkinElement.h"



SkinElement::SkinElement()
{
	elemVertices = NULL;
}


SkinElement::~SkinElement()
{
	SAFE_DELETE(elemVertices);

	ClearVector( vecElemSource );
}



void SkinElement::ReadNode(const DOMNode* node)
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
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}



bool SkinElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemSource.empty() ) { str += L"<source>要素が存在しません\n"; }

	if( elemVertices != NULL ) { elemVertices->ValidElements( str ); }
	else { str += L"<vertices>要素が存在しません\n";  }

	ValidElementsInContainer( vecElemSource, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<skin>\n" + str;
	}

	return str.empty();
}


void SkinElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return ; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
}

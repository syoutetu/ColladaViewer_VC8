#include "stdafx.h"

#include "SceneElement.h"



SceneElement::SceneElement()
{
}


SceneElement::~SceneElement()
{
	ClearVector( vecElemLookat );
	ClearVector( vecElemMatrix );
	ClearVector( vecElemPerspective );
	ClearVector( vecElemRotate );
	ClearVector( vecElemScale );
	ClearVector( vecElemSkew );
	ClearVector( vecElemTranslate );
	ClearVector( vecElemBoundingBox );
	ClearVector( vecElemNode );
	ClearVector( vecElemExtra );
}



void SceneElement::ReadNode(const DOMNode* node)
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
			if( Is_lookat_NodeName( currentNode ) )
			{
				LookatElement* elemLookat = new LookatElement();
				
				elemLookat->ReadNode( currentNode );
				vecElemLookat.push_back( elemLookat );
			}
			else if( Is_matrix_NodeName( currentNode ) )
			{
				MatrixElement* elemMatrix = new MatrixElement();

				elemMatrix->ReadNode( currentNode );
				vecElemMatrix.push_back( elemMatrix );
			}
			else if( Is_perspective_NodeName( currentNode ) )
			{
				PerspectiveElement* elemPerspective = new PerspectiveElement();

				elemPerspective->ReadNode( currentNode );
				vecElemPerspective.push_back( elemPerspective );
			}
			else if( Is_rotate_NodeName( currentNode ) )
			{
				RotateElement* elemRotate = new RotateElement();

				elemRotate->ReadNode( currentNode );
				vecElemRotate.push_back( elemRotate );
			}
			else if( Is_scale_NodeName( currentNode ) )
			{
				ScaleElement* elemScale = new ScaleElement();

				elemScale->ReadNode( currentNode );
				vecElemScale.push_back( elemScale );
			}
			else if( Is_skew_NodeName( currentNode ) )
			{
				SkewElement* elemSkew = new SkewElement();

				elemSkew->ReadNode( currentNode );
				vecElemSkew.push_back( elemSkew );
			}
			else if( Is_translate_NodeName( currentNode ) )
			{
				TranslateElement* elemTranslate = new TranslateElement();

				elemTranslate->ReadNode( currentNode );
				vecElemTranslate.push_back( elemTranslate );
			}
			else if( Is_boundingbox_NodeName( currentNode ) )
			{
				BoundingBoxElement* elemBoundingBox = new BoundingBoxElement();

				elemBoundingBox->ReadNode( currentNode );
				vecElemBoundingBox.push_back( elemBoundingBox );
			}
			else if( Is_node_NodeName( currentNode ) )
			{
				NodeElement* elemNode = new NodeElement();

				elemNode->ReadNode( currentNode );
				vecElemNode.push_back( elemNode );
			}
			else if( Is_extra_NodeName( currentNode ) )
			{
				ExtraElement* elemExtra = new ExtraElement();

				elemExtra->ReadNode( currentNode );
				vecElemExtra.push_back( elemExtra );
			}
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}


bool SceneElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	ValidElementsInContainer( vecElemLookat, str );
	ValidElementsInContainer( vecElemMatrix, str );
	ValidElementsInContainer( vecElemPerspective, str );
	ValidElementsInContainer( vecElemRotate, str );
	ValidElementsInContainer( vecElemScale, str );
	ValidElementsInContainer( vecElemSkew, str );
	ValidElementsInContainer( vecElemTranslate, str );
	ValidElementsInContainer( vecElemBoundingBox, str );
	ValidElementsInContainer( vecElemNode, str );
	ValidElementsInContainer( vecElemExtra, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"・<scene>要素にエラーがあります\n" + str;
	}

	return str.empty();		// エラーがない場合はtureを返す
}



void SceneElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return ; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
}

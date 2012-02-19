#include "stdafx.h"

#include "BoundingBoxElement.h"



BoundingBoxElement::BoundingBoxElement()
{
	elemMin = NULL;
	elemMax = NULL;
}


BoundingBoxElement::~BoundingBoxElement()
{
	SAFE_DELETE(elemMin);
	SAFE_DELETE(elemMax);
}



void BoundingBoxElement::ReadNode(const DOMNode* node)
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
			if( Is_min_NodeName( currentNode ) )
			{
				_ASSERTE(elemMin == NULL);		// 必ず1つ存在するのでこの時点ではNULL
				elemMin = new MinElement();

				elemMin->ReadNode( currentNode );
			}
			else if( Is_max_NodeName( currentNode ) )
			{
				_ASSERTE(elemMax == NULL);		// 必ず1つ存在するのでこの時点ではNULL
				elemMax = new MaxElement();

				elemMax->ReadNode( currentNode );
			}
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}


bool BoundingBoxElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( elemMin == NULL ) { str += L"<min>要素が存在しません\n"; }
	if( elemMax == NULL ) { str += L"<max>要素が存在しません\n"; }

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<boundingbox>\n" + str;
	}

	return str.empty();
}


void BoundingBoxElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetStringValue( attrSubId, Get_sid_Attribute( attr ) );
}

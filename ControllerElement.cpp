#include "stdafx.h"

#include "ControllerElement.h"



ControllerElement::ControllerElement()
{
}


ControllerElement::~ControllerElement()
{
}



void ControllerElement::ReadNode(const DOMNode* node)
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
			if( Is_skin_NodeName( currentNode ) )
			{
				_ASSERTE(elemSkin == NULL);		// 必ず1つ存在するのでこの時点ではNULL
				
				elemSkin = new SkinElement();
				elemSkin->ReadNode( currentNode );
			}
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}


bool ControllerElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( elemSkin != NULL ) { elemSkin->ValidElements( str ); }
	else { str += L"<skin>要素が存在しません\n"; }

	if( attrTarget.empty() ) { str += L"target属性が存在しません\n"; }

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<controller>\n" + str;
	}

	return str.empty();
}


void ControllerElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return ; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
}


#include "stdafx.h"

#include "ExtraElement.h"



ExtraElement::ExtraElement()
{
}


ExtraElement::~ExtraElement()
{
}



void ExtraElement::ReadNode(const DOMNode* node)
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
			if( Is_technique_NodeName( currentNode ) )
			{
				TechniqueElement* elemTechnique = new TechniqueElement();

				elemTechnique->ReadNode( currentNode );
				vecElemTechnique.push_back( elemTechnique );
			}
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}



bool ExtraElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	ValidElementsInContainer( vecElemTechnique, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<extra>\n" + str;
	}

	return str.empty();
}


void ExtraElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
	SetStringValue( attrType, Get_type_Attribute( attr ) );
}
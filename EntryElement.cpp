#include "stdafx.h"

#include "EntryElement.h"



EntryElement::EntryElement()
{
}


EntryElement::~EntryElement()
{
	ClearVector( vecElemParam );
}




void EntryElement::ReadNode(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	ReadAttributes( node );

	DOMNode* currentNode = node->getFirstChild();
	while( currentNode != NULL )
	{
#if _DEBUG	// �f�o�b�O���ɖ��O���`�F�b�N����ׂ�
		const XMLCh* name = currentNode->getNodeName();
#endif

		if( IsElementNode( currentNode ) )
		{
			if( Is_param_NodeName( currentNode ) )
			{
				ParamElement* elemParam = new ParamElement();
				
				elemParam->ReadNode( currentNode );
				vecElemParam.push_back( elemParam );
			}
		}

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}



bool EntryElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( attrFunction.empty() ) { str += L"function���������݂��܂���\n"; }

	ValidElementsInContainer( vecElemParam, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<entry>\n" + str;
	}

	return str.empty();
}



void EntryElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetStringValue( attrFunction, Get_function_Attribute( attr ) );
	SetStringValue( attrSemantic, Get_semantic_Attribute( attr ) );
}
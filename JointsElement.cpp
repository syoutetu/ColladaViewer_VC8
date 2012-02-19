#include "stdafx.h"

#include "JointsElement.h"



JointsElement::JointsElement()
{
	attrCount = 0;		// ������
}


JointsElement::~JointsElement()
{
	ClearVector(vecElemInput);
}



void JointsElement::ReadNode(const DOMNode* node)
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
			if( Is_input_NodeName( currentNode ) )
			{
				InputElement* elemInput = new InputElement();

				elemInput->ReadNode( currentNode );
				vecElemInput.push_back( elemInput );
			}
		}

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}


bool JointsElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemInput.size() < 2 ) { str += L"<input>�v�f��2�ȏ㑶�݂��܂���\n"; }

	ValidElementsInContainer( vecElemInput, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<joints>\n" + str;
	}

	return str.empty();
}


void JointsElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
	SetUIntValue( attrCount, Get_count_Attribute( attr ) );
}

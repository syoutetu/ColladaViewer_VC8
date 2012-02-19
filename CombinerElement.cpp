#include "stdafx.h"

#include "CombinerElement.h"



CombinerElement::CombinerElement()
{
	attrCount = (unsigned int)-1;
}


CombinerElement::~CombinerElement()
{	
	ClearVector(vecElemInput);
	ClearVector(vecElemValue);
}



void CombinerElement::ReadNode(const DOMNode* node)
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
			else if( Is_v_NodeName( currentNode ) )
			{
				ValueElement* elemValue = new ValueElement();

				elemValue->ReadNode( currentNode );
				vecElemValue.push_back( elemValue );
			}
		}

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}


bool CombinerElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( attrCount == (unsigned int)-1 ) { str += L"count���������݂��܂���\n"; }

	if( vecElemInput.size() < 2 ) { str += L"<input>�v�f��2�ȏ㑶�݂��܂���\n"; }
	if( vecElemValue.empty() ) { str +=L"<v>�v�f�����݂��܂���\n"; }

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<combiner>\n" + str;
	}

	return str.empty();
}


void CombinerElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetUIntValue( attrCount, Get_count_Attribute( attr ) );
}

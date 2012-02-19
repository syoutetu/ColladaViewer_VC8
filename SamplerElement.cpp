#include "stdafx.h"

#include "SamplerElement.h"



SamplerElement::SamplerElement()
{
}


SamplerElement::~SamplerElement()
{
	ClearVector( vecElemInput );
}



void SamplerElement::ReadNode(const DOMNode* node)
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


bool SamplerElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemInput.empty() ) { str += L"<input>�v�f�����݂��܂���\n"; }

	ValidElementsInContainer( vecElemInput, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<sampler>\n" + str;
	}

	return str.empty();
}


void SamplerElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
}

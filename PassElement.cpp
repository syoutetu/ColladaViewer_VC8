#include "stdafx.h"

#include "PassElement.h"



PassElement::PassElement()
{
	elemProgram = NULL;
}


PassElement::~PassElement()
{
	SAFE_DELETE(elemProgram);

	ClearVector( vecElemParam );
	ClearVector( vecElemInput );
}



void PassElement::ReadNode(const DOMNode* node)
{
	_ASSERTE(node != NULL);

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
			else if( Is_input_NodeName( currentNode ) )
			{
				InputElement* elemInput = new InputElement();

				elemInput->ReadNode( currentNode );
				vecElemInput.push_back( elemInput );
			}
			else if( Is_program_NodeName( currentNode ) )
			{
				_ASSERTE(elemProgram == NULL);		// 0�܂���1���݂���̂ł��̎��_�ł�NULL
				elemProgram = new ProgramElement();

				elemProgram->ReadNode( currentNode );
			}
		}

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}



bool PassElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( elemProgram != NULL ) { elemProgram->ValidElements( str ); }

	ValidElementsInContainer( vecElemParam, str );
	ValidElementsInContainer( vecElemInput, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<pass>\n" + str;
	}

	return str.empty();
}
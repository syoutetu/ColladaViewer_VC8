#include "stdafx.h"

#include "ImagerElement.h"



ImagerElement::ImagerElement()
{
	elemProgram = NULL;
}


ImagerElement::~ImagerElement()
{
	SAFE_DELETE(elemProgram);
}



void ImagerElement::ReadNode(const DOMNode* node)
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
			if( Is_program_NodeName( currentNode ) )
			{
				_ASSERTE(elemProgram == NULL);		// �K��1���݂���̂ł��̎��_�ł�NULL
				elemProgram = new ProgramElement();

				elemProgram->ReadNode( currentNode );
			}
		}

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}


bool ImagerElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( elemProgram != NULL ) { elemProgram->ValidElements( str ); }
	else { str += L"<program>�v�f�����݂��܂���\n"; }

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<imager>\n" + str;
	}

	return str.empty();
}

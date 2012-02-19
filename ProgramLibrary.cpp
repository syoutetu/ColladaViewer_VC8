#include "stdafx.h"

#include "ProgramLibrary.h"



ProgramLibrary::ProgramLibrary(): LibraryElement(TYPE_PROGRAM)
{
}


ProgramLibrary::~ProgramLibrary()
{
	ClearVector( vecElemProgram );
}



void ProgramLibrary::ReadNode(const DOMNode* node)
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
				ProgramElement* elemProgram = new ProgramElement();

				elemProgram->ReadNode( currentNode );
				vecElemProgram.push_back( elemProgram );
			}
		}

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}



bool ProgramLibrary::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemProgram.empty() ) { str += L"program�v�f�����݂��܂���\n"; }

	ValidElementsInContainer( vecElemProgram, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"�E<library>�v�f(PROGRAM)�ɃG���[������܂�\n" + str;
	}

	return str.empty();
}
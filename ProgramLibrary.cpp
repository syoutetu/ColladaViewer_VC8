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
#if _DEBUG	// デバッグ時に名前をチェックする為に
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

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}



bool ProgramLibrary::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemProgram.empty() ) { str += L"program要素が存在しません\n"; }

	ValidElementsInContainer( vecElemProgram, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"・<library>要素(PROGRAM)にエラーがあります\n" + str;
	}

	return str.empty();
}
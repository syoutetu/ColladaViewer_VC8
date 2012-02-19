#include "stdafx.h"

#include "OpticsElement.h"



OpticsElement::OpticsElement()
{
}


OpticsElement::~OpticsElement()
{
	ClearVector( vecElemProgram );
}



void OpticsElement::ReadNode(const DOMNode* node)
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


bool OpticsElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	ValidElementsInContainer( vecElemProgram, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<optics>\n" + str;
	}

	return str.empty();
}

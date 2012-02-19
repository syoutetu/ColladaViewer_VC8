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
#if _DEBUG	// デバッグ時に名前をチェックする為に
		const XMLCh* name = currentNode->getNodeName();
#endif

		if( IsElementNode( currentNode ) )
		{
			if( Is_program_NodeName( currentNode ) )
			{
				_ASSERTE(elemProgram == NULL);		// 必ず1つ存在するのでこの時点ではNULL
				elemProgram = new ProgramElement();

				elemProgram->ReadNode( currentNode );
			}
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}


bool ImagerElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( elemProgram != NULL ) { elemProgram->ValidElements( str ); }
	else { str += L"<program>要素が存在しません\n"; }

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<imager>\n" + str;
	}

	return str.empty();
}

#include "stdafx.h"

#include "CodeLibrary.h"



CodeLibrary::CodeLibrary(): LibraryElement(TYPE_CODE)
{
}


CodeLibrary::~CodeLibrary()
{
	ClearVector( vecElemCode );
}



void CodeLibrary::ReadNode(const DOMNode* node)
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
			if( Is_code_NodeName( currentNode ) )
			{
				CodeElement* elemCode = new CodeElement();

				elemCode->ReadNode( currentNode );
				vecElemCode.push_back( elemCode );
			}
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}



bool CodeLibrary::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemCode.empty() ) { str += L"<code>要素が存在しません\n";  }

	ValidElementsInContainer( vecElemCode, str );
	
	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"・<library>要素(CODE)にエラーがあります\n" + str;
	}

	return str.empty();
}
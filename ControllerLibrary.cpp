#include "stdafx.h"

#include "ControllerLibrary.h"



ControllerLibrary::ControllerLibrary(): LibraryElement(TYPE_CONTROLLER)
{
}


ControllerLibrary::~ControllerLibrary()
{
	ClearVector( vecElemController );
}



void ControllerLibrary::ReadNode(const DOMNode* node)
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
			if( Is_controller_NodeName( currentNode ) )
			{
				ControllerElement* elemController = new ControllerElement();

				elemController->ReadNode( currentNode );
				vecElemController.push_back( elemController );
			}
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}



bool ControllerLibrary::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemController.empty() ) { str += L"<controller>要素が存在しません\n"; }

	ValidElementsInContainer( vecElemController, str );
	
	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"・<library>要素(CONTROLLER)にエラーがあります\n" + str;
	}

	return str.empty();
}
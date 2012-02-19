#include "stdafx.h"

#include "CameraLibrary.h"



CameraLibrary::CameraLibrary(): LibraryElement(TYPE_CAMERA)
{
}


CameraLibrary::~CameraLibrary()
{
	ClearVector( vecElemCamera );
}



void CameraLibrary::ReadNode(const DOMNode* node)
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
			if( Is_camera_NodeName( currentNode ) )
			{
				CameraElement* elemCamera = new CameraElement();

				elemCamera->ReadNode( currentNode );
				vecElemCamera.push_back( elemCamera );
			}
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}



bool CameraLibrary::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemCamera.empty() ) { str += L"<camera>要素が存在しません\n"; }

	ValidElementsInContainer( vecElemCamera, str );
	
	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"・<library>要素(CAMERA)にエラーがあります\n" + str;
	}

	return str.empty();
}
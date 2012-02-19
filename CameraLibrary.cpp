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
#if _DEBUG	// �f�o�b�O���ɖ��O���`�F�b�N����ׂ�
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

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}



bool CameraLibrary::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemCamera.empty() ) { str += L"<camera>�v�f�����݂��܂���\n"; }

	ValidElementsInContainer( vecElemCamera, str );
	
	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"�E<library>�v�f(CAMERA)�ɃG���[������܂�\n" + str;
	}

	return str.empty();
}
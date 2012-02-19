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
#if _DEBUG	// �f�o�b�O���ɖ��O���`�F�b�N����ׂ�
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

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}



bool ControllerLibrary::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemController.empty() ) { str += L"<controller>�v�f�����݂��܂���\n"; }

	ValidElementsInContainer( vecElemController, str );
	
	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"�E<library>�v�f(CONTROLLER)�ɃG���[������܂�\n" + str;
	}

	return str.empty();
}
#include "stdafx.h"

#include "ImageLibrary.h"



ImageLibrary::ImageLibrary(): LibraryElement(TYPE_IMAGE)
{
}


ImageLibrary::~ImageLibrary()
{
	ClearVector( vecElemImage );
}



void ImageLibrary::ReadNode(const DOMNode* node)
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
			if( Is_image_NodeName( currentNode ) )
			{
				ImageElement* elemImage = new ImageElement();

				elemImage->ReadNode( currentNode );
				vecElemImage.push_back( elemImage );
			}
		}

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}



bool ImageLibrary::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemImage.empty() ) { str += L"<image>�v�f�����݂��܂���\n"; }

	ValidElementsInContainer( vecElemImage, str );
	
	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"�E<library>�v�f(IMAGE)�ɃG���[������܂�\n" + str;
	}

	return str.empty();
}
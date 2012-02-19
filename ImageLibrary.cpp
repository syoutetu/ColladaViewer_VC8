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
#if _DEBUG	// デバッグ時に名前をチェックする為に
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

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}



bool ImageLibrary::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemImage.empty() ) { str += L"<image>要素が存在しません\n"; }

	ValidElementsInContainer( vecElemImage, str );
	
	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"・<library>要素(IMAGE)にエラーがあります\n" + str;
	}

	return str.empty();
}
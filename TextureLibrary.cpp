#include "stdafx.h"

#include "TextureLibrary.h"



TextureLibrary::TextureLibrary(): LibraryElement(TYPE_TEXTURE)
{
}


TextureLibrary::~TextureLibrary()
{
	ClearVector( vecElemTexture );
}



void TextureLibrary::ReadNode(const DOMNode* node)
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
			if( Is_texture_NodeName( currentNode ) )
			{
				TextureElement* elemTexture = new TextureElement();

				elemTexture->ReadNode( currentNode );
				vecElemTexture.push_back( elemTexture );
			}
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}



bool TextureLibrary::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemTexture.empty() ) { str += L"texture要素が存在しません\n"; }

	ValidElementsInContainer( vecElemTexture, str );
	
	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"・<library>要素(TEXTURE)にエラーがあります\n" + str;
	}

	return str.empty();
}
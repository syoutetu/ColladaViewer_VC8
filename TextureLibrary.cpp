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
#if _DEBUG	// �f�o�b�O���ɖ��O���`�F�b�N����ׂ�
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

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}



bool TextureLibrary::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemTexture.empty() ) { str += L"texture�v�f�����݂��܂���\n"; }

	ValidElementsInContainer( vecElemTexture, str );
	
	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"�E<library>�v�f(TEXTURE)�ɃG���[������܂�\n" + str;
	}

	return str.empty();
}
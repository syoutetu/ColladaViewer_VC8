#include "stdafx.h"

#include "LightLibrary.h"



LightLibrary::LightLibrary(): LibraryElement(TYPE_LIGHT)
{
}


LightLibrary::~LightLibrary()
{
	ClearVector( vecElemLight );
}




void LightLibrary::ReadNode(const DOMNode* node)
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
			if( Is_light_NodeName( currentNode ) )
			{
				LightElement* elemLight = new LightElement();

				elemLight->ReadNode( currentNode );
				vecElemLight.push_back( elemLight );
			}
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}



bool LightLibrary::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemLight.empty() ) { str += L"<light>要素が存在しません\n"; }

	ValidElementsInContainer( vecElemLight, str );
	
	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"・<library>要素(LIGHT)にエラーがあります\n" + str;
	}

	return str.empty();
}
#include "stdafx.h"

#include "MaterialLibrary.h"



MaterialLibrary::MaterialLibrary(): LibraryElement(TYPE_MATERIAL)
{
}


MaterialLibrary::~MaterialLibrary()
{
	ClearVector( vecElemMaterial );
}



void MaterialLibrary::ReadNode(const DOMNode* node)
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
			if( Is_material_NodeName( currentNode ) )
			{
				MaterialElement* elemMaterial = new MaterialElement();

				elemMaterial->ReadNode( currentNode );
				vecElemMaterial.push_back( elemMaterial );
			}
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}



bool MaterialLibrary::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemMaterial.empty() ) { str += L"<material>要素が存在しません\n"; }

	ValidElementsInContainer( vecElemMaterial, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"・<library>要素(MATERIAL)にエラーがあります\n" + str;
	}

	return str.empty();
}
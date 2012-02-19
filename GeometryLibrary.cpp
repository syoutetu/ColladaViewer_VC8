#include "stdafx.h"

#include "GeometryLibrary.h"



GeometryLibrary::GeometryLibrary(): LibraryElement(TYPE_GEOMETRY)
{
}


GeometryLibrary::~GeometryLibrary()
{
	ClearVector( vecElemGeometry );
}




void GeometryLibrary::ReadNode(const DOMNode* node)
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
			if( Is_geometry_NodeName( currentNode ) )
			{
				GeometryElement* elemGeometry = new GeometryElement();

				elemGeometry->ReadNode( currentNode );
				vecElemGeometry.push_back( elemGeometry );
			}
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}



bool GeometryLibrary::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemGeometry.empty() ) { str += L"<geometry>要素が存在しません\n"; }

	ValidElementsInContainer( vecElemGeometry, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"・<library>要素(GEOMETRY)にエラーがあります\n" + str;
	}

	return str.empty();
}
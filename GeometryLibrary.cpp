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
#if _DEBUG	// �f�o�b�O���ɖ��O���`�F�b�N����ׂ�
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

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}



bool GeometryLibrary::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemGeometry.empty() ) { str += L"<geometry>�v�f�����݂��܂���\n"; }

	ValidElementsInContainer( vecElemGeometry, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"�E<library>�v�f(GEOMETRY)�ɃG���[������܂�\n" + str;
	}

	return str.empty();
}
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
#if _DEBUG	// �f�o�b�O���ɖ��O���`�F�b�N����ׂ�
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

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}



bool MaterialLibrary::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemMaterial.empty() ) { str += L"<material>�v�f�����݂��܂���\n"; }

	ValidElementsInContainer( vecElemMaterial, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"�E<library>�v�f(MATERIAL)�ɃG���[������܂�\n" + str;
	}

	return str.empty();
}
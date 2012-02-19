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
#if _DEBUG	// �f�o�b�O���ɖ��O���`�F�b�N����ׂ�
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

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}



bool LightLibrary::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemLight.empty() ) { str += L"<light>�v�f�����݂��܂���\n"; }

	ValidElementsInContainer( vecElemLight, str );
	
	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"�E<library>�v�f(LIGHT)�ɃG���[������܂�\n" + str;
	}

	return str.empty();
}
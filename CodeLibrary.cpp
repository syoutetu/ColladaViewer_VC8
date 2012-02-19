#include "stdafx.h"

#include "CodeLibrary.h"



CodeLibrary::CodeLibrary(): LibraryElement(TYPE_CODE)
{
}


CodeLibrary::~CodeLibrary()
{
	ClearVector( vecElemCode );
}



void CodeLibrary::ReadNode(const DOMNode* node)
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
			if( Is_code_NodeName( currentNode ) )
			{
				CodeElement* elemCode = new CodeElement();

				elemCode->ReadNode( currentNode );
				vecElemCode.push_back( elemCode );
			}
		}

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}



bool CodeLibrary::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemCode.empty() ) { str += L"<code>�v�f�����݂��܂���\n";  }

	ValidElementsInContainer( vecElemCode, str );
	
	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"�E<library>�v�f(CODE)�ɃG���[������܂�\n" + str;
	}

	return str.empty();
}
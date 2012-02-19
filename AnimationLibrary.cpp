#include "stdafx.h"

#include "AnimationLibrary.h"



AnimationLibrary::AnimationLibrary(): LibraryElement(TYPE_ANIMATION)
{
}


AnimationLibrary::~AnimationLibrary()
{
	ClearVector( vecElemAnimation );
}



void AnimationLibrary::ReadNode(const DOMNode* node)
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
			if( Is_animation_NodeName( currentNode ) )
			{
				AnimationElement* elemAnimation = new AnimationElement();

				elemAnimation->ReadNode( currentNode );
				vecElemAnimation.push_back( elemAnimation );
			}
		}

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}



bool AnimationLibrary::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemAnimation.empty() ) { str += L"<animation>�v�f�����݂��܂���\n"; }

	ValidElementsInContainer( vecElemAnimation, str );
	
	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"�E<library>�v�f(ANIMATION)�ɃG���[������܂�\n" + str;
	}

	return str.empty();
}
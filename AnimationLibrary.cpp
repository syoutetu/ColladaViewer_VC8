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
#if _DEBUG	// デバッグ時に名前をチェックする為に
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

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}



bool AnimationLibrary::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemAnimation.empty() ) { str += L"<animation>要素が存在しません\n"; }

	ValidElementsInContainer( vecElemAnimation, str );
	
	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"・<library>要素(ANIMATION)にエラーがあります\n" + str;
	}

	return str.empty();
}

#pragma once

#if !defined ___AnimationLibrary_h___
#define ___AnimationLibrary_h___

#include "LibraryElement.h"
#include "AnimationElement.h"


// type�A�g���r���[�g��ANIMATION��<library>�G�������g�̏���ۑ�����N���X
class AnimationLibrary: public LibraryElement
{

public:

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	AnimationLibrary();
	~AnimationLibrary();

	unsigned int GetCount() const	{ return (unsigned int)vecElemAnimation.size(); }

	void* GetElement(unsigned int index) const	{ _ASSERTE(index < GetCount()); return vecElemAnimation[index]; }

private:

	VECANIMATIONELEM	vecElemAnimation;
};


#endif	//___AnimationLibrary_h___
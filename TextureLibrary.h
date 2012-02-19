
#pragma once

#if !defined ___TextureLibrary_h___
#define ___TextureLibrary_h___

#include "LibraryElement.h"
#include "TextureElement.h"


// type�A�g���r���[�g��TEXTURE��<library>�G�������g�̏���ۑ�����N���X
class TextureLibrary: public LibraryElement
{

public:

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	TextureLibrary();
	~TextureLibrary();

	unsigned int GetCount() const	{ return (unsigned int)vecElemTexture.size(); }

	void* GetElement(unsigned int index) const	{ _ASSERTE(index < GetCount()); return vecElemTexture[index]; }

private:

	VECTEXTUREELEM	vecElemTexture;
};


#endif	//___TextureLibrary_h___
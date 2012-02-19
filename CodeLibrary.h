
#pragma once

#if !defined ___CodeLibrary_h___
#define ___CodeLibrary_h___

#include "LibraryElement.h"
#include "CodeElement.h"


// type�A�g���r���[�g��CODE��<library>�G�������g�̏���ۑ�����N���X
class CodeLibrary: public LibraryElement
{

public:

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	CodeLibrary();
	~CodeLibrary();

	unsigned int GetCount() const	{ return (unsigned int)vecElemCode.size(); }
	
	void* GetElement(unsigned int index) const	{ _ASSERTE(index < GetCount()); return vecElemCode[index]; }

private:

	VECCODEELEM	vecElemCode;
};


#endif	//___CodeLibrary_h___
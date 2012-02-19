
#pragma once

#if !defined ___MaterialLibrary_h___
#define ___MaterialLibrary_h___

#include "LibraryElement.h"
#include "MaterialElement.h"


// type�A�g���r���[�g��MATERIAL��<library>�G�������g�̏���ۑ�����N���X
class MaterialLibrary: public LibraryElement
{

public:

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	MaterialLibrary();
	~MaterialLibrary();

	unsigned int GetCount() const	{ return (unsigned int)vecElemMaterial.size(); }

	void* GetElement(unsigned int index) const	{ _ASSERTE(index < GetCount()); return vecElemMaterial[index]; }

private:

	VECMATERIALELEM	vecElemMaterial;
};


#endif	//___MaterialLibrary_h___
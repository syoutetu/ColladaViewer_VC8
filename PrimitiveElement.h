
#pragma once

#if !defined ___PrimitiveElement_h___
#define ___PrimitiveElement_h___


#include "DomNodeReader.h"


// <p>�G�������g�̏���ۑ�����N���X
class PrimitiveElement: public DomNodeReader
{

public:

	PrimitiveElement();
	~PrimitiveElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	unsigned int GetCount() const	{ return (unsigned int)valIndices.size(); }
	int GetValue(unsigned int index) const	{ _ASSERTE(index < GetCount()); return valIndices[index]; }

private:

	//====================================
	// �m�[�h�̒l
	//====================================
	std::vector<int>	valIndices;
	
	void ReadValue(const DOMNode* node);
};


typedef std::vector<PrimitiveElement*>	VECPRIMITIVEELEM;


#endif	//___PrimitiveElement_h___
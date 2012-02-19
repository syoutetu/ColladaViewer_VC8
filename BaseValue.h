
#pragma once

#if !defined ___BaseValue_h___
#define ___BaseValue_h___


#include "DomNodeReader.h"

#include "ValueElement.h"


// �e��l�����v�f�N���X�̊��N���X
class BaseValue: public DomNodeReader
{

public:

	virtual ~BaseValue();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
//	bool ValidElements(std::wstring& message) const {return false;} �p���N���X�Ŏ�������


	unsigned int GetCount() const	{ return (unsigned int)valParam.size(); }

protected:

	BaseValue(unsigned int reqCount);		// �C���X�^���X�͍쐬�ł��Ȃ�

	bool ValidElements(std::wstring& message, const wchar_t* nodeName) const;

private:

	//====================================
	// �A�g���r���[�g
	//====================================
	std::wstring	attrSubId;		// �e�̗v�f����Unique, Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// �m�[�h�̒l
	//====================================
	std::vector<float>	valParam;

	void ReadValue(const DOMNode* node);


	const unsigned int requiredCount;	// �K�v�ȃm�[�h�̒l�̐�
};



#endif	//___BaseValue_h___
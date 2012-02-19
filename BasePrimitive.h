
#pragma once

#if !defined ___BasePrimitive_h___
#define ___BasePrimitive_h___


#include "DomNodeReader.h"

#include "InputElement.h"
#include "PrimitiveElement.h"
#include "ParamElement.h"



// �e��v���~�e�B�u�����v�f�N���X�̊��N���X
class BasePrimitive: public DomNodeReader
{

public:

	virtual ~BasePrimitive();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
//	bool ValidElements(std::wstring& message) const;	�p���N���X�Ŏ�������


	unsigned int GetInputCount() const	{ return (unsigned int)vecElemInput.size(); }
	InputElement* GetInputElement(unsigned int index) const	{ _ASSERTE(index < GetInputCount()); return vecElemInput[index]; }
	InputElement* GetInputElementByAttrIdx(unsigned int idx) const;	// idx�A�g���r���[�g���w�肵�Ď擾����

	unsigned int GetParamCount() const	{ return (unsigned int)vecElemParam.size(); }
	
	unsigned int GetPrimitiveCount() const	{ return (unsigned int)vecElemP.size(); }
	PrimitiveElement* GetPrimitiveElement(unsigned int index) const	{ _ASSERTE(index < GetPrimitiveCount()); return vecElemP[index]; }

protected:

	BasePrimitive();		// �C���X�^���X�͍쐬�ł��Ȃ�

	bool ValidElements(std::wstring& message, const wchar_t* nodeName) const;

private:

	//====================================
	// �A�g���r���[�g
	//====================================
	unsigned int	attrCount;		// Required
	std::wstring	attrMaterial;	// Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// �G�������g
	//====================================
	VECINPUTELEM	vecElemInput;		// 0�ȏ㑶�݂���
	VECPARAMELEM	vecElemParam;		// 0�ȏ㑶�݂���
	VECPRIMITIVEELEM	vecElemP;		// 0�ȏ㑶�݂���
};



#endif	//___BasePrimitive_h___
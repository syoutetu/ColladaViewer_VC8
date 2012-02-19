
#pragma once

#if !defined ___CombinerElement_h___
#define ___CombinerElement_h___


#include "DomNodeReader.h"

#include "InputElement.h"
#include "ValueElement.h"


// <combiner>�G�������g�̏���ۑ�����N���X
class CombinerElement: public DomNodeReader
{

public:

	CombinerElement();
	~CombinerElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// �A�g���r���[�g
	//====================================
	unsigned int		attrCount;		// Required

	void ReadAttributes(const DOMNode* node);


	//====================================
	// �G�������g
	//====================================
	VECINPUTELEM		vecElemInput;		// 2�ȏ㑶�݂���
	VECVALUEELEM		vecElemValue;		// 1�ȏ㑶�݂���

};


typedef std::vector<CombinerElement*>	VECCOMBINERELEM;


#endif	//___CombinerElement_h___
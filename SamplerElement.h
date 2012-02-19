
#pragma once

#if !defined ___SamplerElement_h___
#define ___SamplerElement_h___


#include "DomNodeReader.h"

#include "InputElement.h"


// <sampler>�G�������g�̏���ۑ�����N���X
class SamplerElement: public DomNodeReader
{

public:

	SamplerElement();
	~SamplerElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// �A�g���r���[�g
	//====================================
	std::wstring	attrId;		// �h�L�������g����Unique, Optional
	std::wstring	attrName;	// Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// �G�������g
	//====================================
	VECINPUTELEM		vecElemInput;			// 1�ȏ㑶�݂���
};


typedef std::vector<SamplerElement*>	VECSAMPLERELEM;


#endif	//___SamplerElement_h___
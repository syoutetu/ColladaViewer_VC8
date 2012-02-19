
#pragma once

#if !defined ___ExtraElement_h___
#define ___ExtraElement_h___


#include "DomNodeReader.h"

#include "TechniqueElement.h"


// <extra>�G�������g�̏���ۑ�����N���X
class ExtraElement: public DomNodeReader
{

public:

	ExtraElement();
	~ExtraElement();

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
	std::wstring	attrType;	// Optional

	void ReadAttributes(const DOMNode* node);



	//====================================
	// �G�������g
	//====================================
	VECTECHNIQUEELEM	vecElemTechnique;		// 0�ȏ㑶�݂���

};


typedef std::vector<ExtraElement*>	VECEXTRAELEM;


#endif	//___ExtraElement_h___
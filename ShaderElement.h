
#pragma once

#if !defined ___ShaderElement_h___
#define ___ShaderElement_h___

#include "DomNodeReader.h"

#include "ParamElement.h"
#include "TechniqueElement.h"


// <shader>�G�������g�̏���ۑ�����N���X
class ShaderElement: public DomNodeReader
{
public:

	ShaderElement();
	~ShaderElement();

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
	VECPARAMELEM		vecElemParam;		// 0�ȏ㑶�݂���
	VECTECHNIQUEELEM	vecElemTechnique;	// 1�ȏ㑶�݂���
};


typedef std::vector<ShaderElement*>	VECSHADERELEM;


#endif	//___ShaderElement_h___
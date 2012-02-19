
#pragma once

#if !defined ___PassElement_h___
#define ___PassElement_h___


#include "DomNodeReader.h"

#include "ParamElement.h"
#include "InputElement.h"
#include "ProgramElement.h"


// <pass>�G�������g�̏���ۑ�����N���X
class PassElement: public DomNodeReader
{
public:

	PassElement();
	~PassElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// �G�������g
	//====================================
	VECPARAMELEM		vecElemParam;		// 0�ȏ㑶�݂���
	VECINPUTELEM		vecElemInput;		// 0�ȏ㑶�݂���
	ProgramElement*		elemProgram;		// 0�܂���1���݂���
};


typedef std::vector<PassElement*>	VECPASSELEM;


#endif	//___PassElement_h___
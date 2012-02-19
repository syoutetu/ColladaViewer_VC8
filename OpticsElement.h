
#pragma once

#if !defined ___OpticsElement_h___
#define ___OpticsElement_h___


#include "DomNodeReader.h"

#include "TechniqueElement.h"
#include "ProgramElement.h"


// <optics>�G�������g�̏���ۑ�����N���X
class OpticsElement: public DomNodeReader
{

public:

	OpticsElement();
	~OpticsElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// �G�������g
	//====================================
	VECPROGRAMELEM		vecElemProgram;			// 0�ȏ㑶�݂���H
};


typedef std::vector<OpticsElement*>	VECOPTICSELEM;


#endif	//___OpticsElement_h___
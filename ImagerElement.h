
#pragma once

#if !defined ___ImagerElement_h___
#define ___ImagerElement_h___


#include "DomNodeReader.h"

#include "ProgramElement.h"


// <imager>�G�������g�̏���ۑ�����N���X
class ImagerElement: public DomNodeReader
{

public:

	ImagerElement();
	~ImagerElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// �G�������g
	//====================================
	ProgramElement*		elemProgram;		// �K��1���݂���H

};


typedef std::vector<ImagerElement*>	VECIMAGERELEM;


#endif	//___ImagerElement_h___
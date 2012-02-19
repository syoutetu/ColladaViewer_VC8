
#pragma once

#if !defined ___ValueElement_h___
#define ___ValueElement_h___


#include "DomNodeReader.h"


// <v>�G�������g�̏���ۑ�����N���X
class ValueElement: public DomNodeReader
{

public:

	ValueElement();
	~ValueElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// �m�[�h�̒l
	//====================================
	std::vector<int>	valIndices;

	void ReadValue(const DOMNode* node);
};


typedef std::vector<ValueElement*>	VECVALUEELEM;


#endif	//___ValueElement_h___
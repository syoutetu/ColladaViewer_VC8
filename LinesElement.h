
#pragma once

#if !defined ___LinesElement_h___
#define ___LinesElement_h___


#include "BasePrimitive.h"


// <lines>�G�������g�̏���ۑ�����N���X
class LinesElement: public BasePrimitive
{

public:

	LinesElement()	{}
	~LinesElement()	{}

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BasePrimitive::ValidElements( message, L"lines" ); }

private:


};


typedef std::vector<LinesElement*>	VECLINESELEM;


#endif	//___LinesElement_h___
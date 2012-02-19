
#pragma once

#if !defined ___MaxElement_h___
#define ___MaxElement_h___


#include "BaseValue.h"


// <max>�G�������g�̏���ۑ�����N���X
class MaxElement: public BaseValue
{

public:

	MaxElement(): BaseValue( 3 )	{}	// 3float�K�v
	~MaxElement()	{}

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BaseValue::ValidElements( message, L"max" ); }

private:


};


typedef std::vector<MaxElement*>	VECMAXELEM;


#endif	//___MaxElement_h___
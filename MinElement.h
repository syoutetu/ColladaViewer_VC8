
#pragma once

#if !defined ___MinElement_h___
#define ___MinElement_h___


#include "BaseValue.h"


// <min>�G�������g�̏���ۑ�����N���X
class MinElement: public BaseValue
{

public:

	MinElement():BaseValue( 3 )	{}	// 3float�K�v
	~MinElement()	{}

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BaseValue::ValidElements( message, L"min" ); }

private:


};


typedef std::vector<MinElement*>	VECMINELEM;


#endif	//___MinElement_h___
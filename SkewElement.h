
#pragma once

#if !defined ___SkewElement_h___
#define ___SkewElement_h___


#include "BaseValue.h"


// <skew>�G�������g�̏���ۑ�����N���X
class SkewElement: public BaseValue
{

public:

	SkewElement(): BaseValue( 7 )	{}	// (1 + 3 + 3)float�K�v
	~SkewElement()	{}

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BaseValue::ValidElements( message, L"skew" ); }

private:


};


typedef std::vector<SkewElement*>	VECSKEWELEM;


#endif	//___SkewElement_h___
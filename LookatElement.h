
#pragma once

#if !defined ___LookatElement_h___
#define ___LookatElement_h___


#include "BaseValue.h"


// <lookat>�G�������g�̏���ۑ�����N���X
class LookatElement: public BaseValue
{

public:

	LookatElement():BaseValue( 9 )	{}	// 3x3float�K�v
	~LookatElement()	{}

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BaseValue::ValidElements( message, L"lookat" ); }

private:


};


typedef std::vector<LookatElement*>	VECLOOKATELEM;


#endif	//___LookatElement_h___
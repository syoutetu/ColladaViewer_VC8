
#pragma once

#if !defined ___RotateElement_h___
#define ___RotateElement_h___


#include "BaseValue.h"


// <rotate>�G�������g�̏���ۑ�����N���X
class RotateElement: public BaseValue
{

public:

	RotateElement(): BaseValue( 3 )	{}	// 3float�K�v
	~RotateElement()	{}

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BaseValue::ValidElements( message, L"rotate" ); }

private:


};


typedef std::vector<RotateElement*>	VECROTATEELEM;


#endif	//___RotateElement_h___
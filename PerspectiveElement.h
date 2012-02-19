
#pragma once

#if !defined ___PerspectiveElement_h___
#define ___PerspectiveElement_h___


#include "BaseValue.h"


// <perspective>�G�������g�̏���ۑ�����N���X
class PerspectiveElement: public BaseValue
{

public:

	PerspectiveElement(): BaseValue( 1 )	{}	// 1float�K�v
	~PerspectiveElement()	{}

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BaseValue::ValidElements( message, L"perspective" ); }

private:


};


typedef std::vector<PerspectiveElement*>	VECPERSPECTIVEELEM;


#endif	//___PerspectiveElement_h___
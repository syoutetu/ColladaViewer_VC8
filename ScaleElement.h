
#pragma once

#if !defined ___ScaleElement_h___
#define ___ScaleElement_h___


#include "BaseValue.h"


// <scale>�G�������g�̏���ۑ�����N���X
class ScaleElement: public BaseValue
{

public:

	ScaleElement(): BaseValue( 3 )	{}	// 3float�K�v
	~ScaleElement()	{}

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BaseValue::ValidElements( message, L"scale" ); }

private:


};


typedef std::vector<ScaleElement*>	VECSCALEELEM;


#endif	//___ScaleElement_h___
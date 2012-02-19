
#pragma once

#if !defined ___TranslateElement_h___
#define ___TranslateElement_h___


#include "BaseValue.h"


// <translate>�G�������g�̏���ۑ�����N���X
class TranslateElement: public BaseValue
{

public:

	TranslateElement(): BaseValue( 3 )	{}	// 3float�K�v
	~TranslateElement()	{}

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BaseValue::ValidElements( message, L"translate" ); }

private:


};


typedef std::vector<TranslateElement*>	VECTRANSLATEELEM;


#endif	//___TranslateElement_h___
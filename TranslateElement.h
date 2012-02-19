
#pragma once

#if !defined ___TranslateElement_h___
#define ___TranslateElement_h___


#include "BaseValue.h"


// <translate>エレメントの情報を保存するクラス
class TranslateElement: public BaseValue
{

public:

	TranslateElement(): BaseValue( 3 )	{}	// 3float必要
	~TranslateElement()	{}

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BaseValue::ValidElements( message, L"translate" ); }

private:


};


typedef std::vector<TranslateElement*>	VECTRANSLATEELEM;


#endif	//___TranslateElement_h___
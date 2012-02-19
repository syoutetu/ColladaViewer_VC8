
#pragma once

#if !defined ___MaxElement_h___
#define ___MaxElement_h___


#include "BaseValue.h"


// <max>エレメントの情報を保存するクラス
class MaxElement: public BaseValue
{

public:

	MaxElement(): BaseValue( 3 )	{}	// 3float必要
	~MaxElement()	{}

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BaseValue::ValidElements( message, L"max" ); }

private:


};


typedef std::vector<MaxElement*>	VECMAXELEM;


#endif	//___MaxElement_h___
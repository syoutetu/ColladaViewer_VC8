
#pragma once

#if !defined ___MinElement_h___
#define ___MinElement_h___


#include "BaseValue.h"


// <min>エレメントの情報を保存するクラス
class MinElement: public BaseValue
{

public:

	MinElement():BaseValue( 3 )	{}	// 3float必要
	~MinElement()	{}

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BaseValue::ValidElements( message, L"min" ); }

private:


};


typedef std::vector<MinElement*>	VECMINELEM;


#endif	//___MinElement_h___
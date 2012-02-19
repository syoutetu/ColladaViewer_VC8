
#pragma once

#if !defined ___SkewElement_h___
#define ___SkewElement_h___


#include "BaseValue.h"


// <skew>エレメントの情報を保存するクラス
class SkewElement: public BaseValue
{

public:

	SkewElement(): BaseValue( 7 )	{}	// (1 + 3 + 3)float必要
	~SkewElement()	{}

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BaseValue::ValidElements( message, L"skew" ); }

private:


};


typedef std::vector<SkewElement*>	VECSKEWELEM;


#endif	//___SkewElement_h___
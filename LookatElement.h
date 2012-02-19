
#pragma once

#if !defined ___LookatElement_h___
#define ___LookatElement_h___


#include "BaseValue.h"


// <lookat>エレメントの情報を保存するクラス
class LookatElement: public BaseValue
{

public:

	LookatElement():BaseValue( 9 )	{}	// 3x3float必要
	~LookatElement()	{}

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BaseValue::ValidElements( message, L"lookat" ); }

private:


};


typedef std::vector<LookatElement*>	VECLOOKATELEM;


#endif	//___LookatElement_h___
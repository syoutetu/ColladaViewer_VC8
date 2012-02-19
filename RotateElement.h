
#pragma once

#if !defined ___RotateElement_h___
#define ___RotateElement_h___


#include "BaseValue.h"


// <rotate>エレメントの情報を保存するクラス
class RotateElement: public BaseValue
{

public:

	RotateElement(): BaseValue( 3 )	{}	// 3float必要
	~RotateElement()	{}

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BaseValue::ValidElements( message, L"rotate" ); }

private:


};


typedef std::vector<RotateElement*>	VECROTATEELEM;


#endif	//___RotateElement_h___
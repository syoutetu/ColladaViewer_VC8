
#pragma once

#if !defined ___ScaleElement_h___
#define ___ScaleElement_h___


#include "BaseValue.h"


// <scale>エレメントの情報を保存するクラス
class ScaleElement: public BaseValue
{

public:

	ScaleElement(): BaseValue( 3 )	{}	// 3float必要
	~ScaleElement()	{}

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BaseValue::ValidElements( message, L"scale" ); }

private:


};


typedef std::vector<ScaleElement*>	VECSCALEELEM;


#endif	//___ScaleElement_h___
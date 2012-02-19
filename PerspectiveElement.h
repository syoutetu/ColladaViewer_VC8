
#pragma once

#if !defined ___PerspectiveElement_h___
#define ___PerspectiveElement_h___


#include "BaseValue.h"


// <perspective>エレメントの情報を保存するクラス
class PerspectiveElement: public BaseValue
{

public:

	PerspectiveElement(): BaseValue( 1 )	{}	// 1float必要
	~PerspectiveElement()	{}

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BaseValue::ValidElements( message, L"perspective" ); }

private:


};


typedef std::vector<PerspectiveElement*>	VECPERSPECTIVEELEM;


#endif	//___PerspectiveElement_h___
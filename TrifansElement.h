
#pragma once

#if !defined ___TrifansElement_h___
#define ___TrifansElement_h___


#include "BasePrimitive.h"


// <trifans>エレメントの情報を保存するクラス
class TrifansElement: public BasePrimitive
{

public:

	TrifansElement()	{}
	~TrifansElement()	{}

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BasePrimitive::ValidElements( message, L"trifans" ); }

private:


};


typedef std::vector<TrifansElement*>	VECTRIFANSELEM;


#endif	//___TrifansElement_h___
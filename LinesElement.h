
#pragma once

#if !defined ___LinesElement_h___
#define ___LinesElement_h___


#include "BasePrimitive.h"


// <lines>エレメントの情報を保存するクラス
class LinesElement: public BasePrimitive
{

public:

	LinesElement()	{}
	~LinesElement()	{}

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BasePrimitive::ValidElements( message, L"lines" ); }

private:


};


typedef std::vector<LinesElement*>	VECLINESELEM;


#endif	//___LinesElement_h___
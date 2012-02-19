
#pragma once

#if !defined ___LinestripsElement_h___
#define ___LinestripsElement_h___


#include "BasePrimitive.h"


// <linestrips>エレメントの情報を保存するクラス
class LinestripsElement: public BasePrimitive
{

public:

	LinestripsElement()		{}
	~LinestripsElement()	{}

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BasePrimitive::ValidElements( message, L"linestrips" ); }

private:


};


typedef std::vector<LinestripsElement*>	VECLINESTRIPSELEM;


#endif	//___LinestripsElement_h___
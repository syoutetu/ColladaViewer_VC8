
#pragma once

#if !defined ___TristripsElement_h___
#define ___TristripsElement_h___


#include "BasePrimitive.h"


// <tristrips>エレメントの情報を保存するクラス
class TristripsElement: public BasePrimitive
{

public:

	TristripsElement()	{}
	~TristripsElement()	{}

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BasePrimitive::ValidElements( message, L"tristrips" ); }

private:


};


typedef std::vector<TristripsElement*>	VECTRISTRIPSELEM;


#endif	//___TristripsElement_h___
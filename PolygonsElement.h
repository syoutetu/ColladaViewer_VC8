
#pragma once

#if !defined ___PolygonsElement_h___
#define ___PolygonsElement_h___


#include "BasePrimitive.h"


// <polygons>エレメントの情報を保存するクラス
class PolygonsElement: public BasePrimitive
{

public:

	PolygonsElement()	{}
	~PolygonsElement()	{}

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BasePrimitive::ValidElements( message, L"polygons" ); }

private:


};


typedef std::vector<PolygonsElement*>	VECPOLYGONSELEM;


#endif	//___PolygonsElement_h___
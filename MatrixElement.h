
#pragma once

#if !defined ___MatrixElement_h___
#define ___MatrixElement_h___


#include "BaseValue.h"


// <matrix>エレメントの情報を保存するクラス
class MatrixElement: public BaseValue
{

public:

	MatrixElement(): BaseValue( 16 )	{}	// 4x4float必要
	~MatrixElement()	{}

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BaseValue::ValidElements( message, L"matrix" ); }

private:


};


typedef std::vector<MatrixElement*>	VECMATRIXELEM;


#endif	//___MatrixElement_h___
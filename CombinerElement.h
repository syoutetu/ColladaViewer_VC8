
#pragma once

#if !defined ___CombinerElement_h___
#define ___CombinerElement_h___


#include "DomNodeReader.h"

#include "InputElement.h"
#include "ValueElement.h"


// <combiner>エレメントの情報を保存するクラス
class CombinerElement: public DomNodeReader
{

public:

	CombinerElement();
	~CombinerElement();

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// アトリビュート
	//====================================
	unsigned int		attrCount;		// Required

	void ReadAttributes(const DOMNode* node);


	//====================================
	// エレメント
	//====================================
	VECINPUTELEM		vecElemInput;		// 2つ以上存在する
	VECVALUEELEM		vecElemValue;		// 1つ以上存在する

};


typedef std::vector<CombinerElement*>	VECCOMBINERELEM;


#endif	//___CombinerElement_h___
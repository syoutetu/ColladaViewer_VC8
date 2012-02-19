
#pragma once

#if !defined ___ValueElement_h___
#define ___ValueElement_h___


#include "DomNodeReader.h"


// <v>エレメントの情報を保存するクラス
class ValueElement: public DomNodeReader
{

public:

	ValueElement();
	~ValueElement();

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// ノードの値
	//====================================
	std::vector<int>	valIndices;

	void ReadValue(const DOMNode* node);
};


typedef std::vector<ValueElement*>	VECVALUEELEM;


#endif	//___ValueElement_h___
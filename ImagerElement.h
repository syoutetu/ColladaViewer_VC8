
#pragma once

#if !defined ___ImagerElement_h___
#define ___ImagerElement_h___


#include "DomNodeReader.h"

#include "ProgramElement.h"


// <imager>エレメントの情報を保存するクラス
class ImagerElement: public DomNodeReader
{

public:

	ImagerElement();
	~ImagerElement();

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// エレメント
	//====================================
	ProgramElement*		elemProgram;		// 必ず1つ存在する？

};


typedef std::vector<ImagerElement*>	VECIMAGERELEM;


#endif	//___ImagerElement_h___
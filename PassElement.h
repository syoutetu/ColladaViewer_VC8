
#pragma once

#if !defined ___PassElement_h___
#define ___PassElement_h___


#include "DomNodeReader.h"

#include "ParamElement.h"
#include "InputElement.h"
#include "ProgramElement.h"


// <pass>エレメントの情報を保存するクラス
class PassElement: public DomNodeReader
{
public:

	PassElement();
	~PassElement();

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// エレメント
	//====================================
	VECPARAMELEM		vecElemParam;		// 0以上存在する
	VECINPUTELEM		vecElemInput;		// 0以上存在する
	ProgramElement*		elemProgram;		// 0または1つ存在する
};


typedef std::vector<PassElement*>	VECPASSELEM;


#endif	//___PassElement_h___
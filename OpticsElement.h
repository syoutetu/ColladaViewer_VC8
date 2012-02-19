
#pragma once

#if !defined ___OpticsElement_h___
#define ___OpticsElement_h___


#include "DomNodeReader.h"

#include "TechniqueElement.h"
#include "ProgramElement.h"


// <optics>エレメントの情報を保存するクラス
class OpticsElement: public DomNodeReader
{

public:

	OpticsElement();
	~OpticsElement();

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// エレメント
	//====================================
	VECPROGRAMELEM		vecElemProgram;			// 0以上存在する？
};


typedef std::vector<OpticsElement*>	VECOPTICSELEM;


#endif	//___OpticsElement_h___
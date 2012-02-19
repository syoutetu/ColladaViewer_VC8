
#pragma once

#if !defined ___ExtraElement_h___
#define ___ExtraElement_h___


#include "DomNodeReader.h"

#include "TechniqueElement.h"


// <extra>エレメントの情報を保存するクラス
class ExtraElement: public DomNodeReader
{

public:

	ExtraElement();
	~ExtraElement();

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// アトリビュート
	//====================================
	std::wstring	attrId;		// ドキュメント内でUnique, Optional
	std::wstring	attrName;	// Optional
	std::wstring	attrType;	// Optional

	void ReadAttributes(const DOMNode* node);



	//====================================
	// エレメント
	//====================================
	VECTECHNIQUEELEM	vecElemTechnique;		// 0以上存在する

};


typedef std::vector<ExtraElement*>	VECEXTRAELEM;


#endif	//___ExtraElement_h___
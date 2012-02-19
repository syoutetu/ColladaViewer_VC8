
#pragma once

#if !defined ___EntryElement_h___
#define ___EntryElement_h___


#include "DomNodeReader.h"

#include "ParamElement.h"


// <entry>エレメントの情報を保存するクラス
class EntryElement: public DomNodeReader
{
public:

	EntryElement();
	~EntryElement();


	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// アトリビュート
	//====================================
	std::wstring		attrFunction;	// Required
	std::wstring		attrSemantic;	// Optional
	
	void ReadAttributes(const DOMNode* node);


	//====================================
	// エレメント
	//====================================
	VECPARAMELEM		vecElemParam;	// 0以上存在する
};


typedef std::vector<EntryElement*>	VECENTRYELEM;


#endif	//___EntryElement_h___
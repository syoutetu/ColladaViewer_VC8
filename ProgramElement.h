
#pragma once

#if !defined ___ProgramElement_h___
#define ___ProgramElement_h___


#include "DomNodeReader.h"

#include "AssetElement.h"
#include "CodeElement.h"
#include "EntryElement.h"
#include "ParamElement.h"


// <program>エレメントの情報を保存するクラス
class ProgramElement
{
public:

	ProgramElement();
	~ProgramElement();

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// アトリビュート
	//====================================
	std::wstring		attrId;		// ドキュメント内でUnique, Optional
	std::wstring		attrName;	// Optional
	std::wstring		attrUrl;	// Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// エレメント
	//====================================
	AssetElement*		elemAsset;		// 0または1つ存在する？
	CodeElement*		elemCode;		// 0または1つ存在する
	EntryElement*		elemEntry;		// 0または1つ存在する？
	VECPARAMELEM		vecElemParam;	// 0以上存在する
};


typedef std::vector<ProgramElement*>	VECPROGRAMELEM;


#endif	//___ProgramElement_h___
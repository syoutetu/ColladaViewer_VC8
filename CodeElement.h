
#pragma once

#if !defined ___CodeElement_h___
#define ___CodeElement_h___


#include "DomNodeReader.h"


// <code>エレメントの情報を保存するクラス
class CodeElement: public DomNodeReader
{
public:

	CodeElement();
	~CodeElement();


	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// アトリビュート
	//====================================
	std::wstring		attrId;			// ドキュメント内でUnique, Optional
	std::wstring		attrLang;		// Required
	std::wstring		attrProfile;	// Optional
	std::wstring		attrSemantic;	// Optional
	std::wstring		attrUrl;		// Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// ノードの値
	//====================================
	std::wstring		valCode;

	void ReadValue(const DOMNode* node);
};


typedef std::vector<CodeElement*>	VECCODEELEM;


#endif	//___CodeElement_h___
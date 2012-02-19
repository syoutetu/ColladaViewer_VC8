
#pragma once

#if !defined ___SkinElement_h___
#define ___SkinElement_h___


#include "DomNodeReader.h"

#include "SourceElement.h"
#include "VerticesElement.h"


// <skin>エレメントの情報を保存するクラス
class SkinElement: public DomNodeReader
{
public:

	SkinElement();
	~SkinElement();


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

	void ReadAttributes(const DOMNode* node);


	//====================================
	// エレメント
	//====================================
	VECSOURCEELEM		vecElemSource;		// 1つ以上存在する
	VerticesElement*	elemVertices;		// 必ず1つ存在する
};


typedef std::vector<SkinElement*>	VECSKINELEM;


#endif	//___SkinElement_h___
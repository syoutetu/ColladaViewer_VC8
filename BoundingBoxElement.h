
#pragma once

#if !defined ___BoundingBoxElement_h___
#define ___BoundingBoxElement_h___


#include "DomNodeReader.h"

#include "MinElement.h"
#include "MaxElement.h"


// <boundingbox>エレメントの情報を保存するクラス
class BoundingBoxElement: public DomNodeReader
{

public:

	BoundingBoxElement();
	~BoundingBoxElement();

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// アトリビュート
	//====================================
	std::wstring	attrSubId;		// 親の要素内でUnique, Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// エレメント
	//====================================
	MinElement*		elemMin;		// 必ず1つ存在する
	MaxElement*		elemMax;		// 必ず1つ存在する

};


typedef std::vector<BoundingBoxElement*>	VECBOUNDINGBOXELEM;


#endif	//___BoundingBoxElement_h___
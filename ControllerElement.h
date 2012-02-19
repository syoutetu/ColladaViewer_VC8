
#pragma once

#if !defined ___ControllerElement_h___
#define ___ControllerElement_h___


#include "DomNodeReader.h"

#include "SkinElement.h"


// <controller>エレメントの情報を保存するクラス
class ControllerElement: public DomNodeReader
{
public:

	ControllerElement();
	~ControllerElement();


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
	std::wstring		attrName;		// Optional
	std::wstring		attrTarget;		// Required

	void ReadAttributes(const DOMNode* node);


	//====================================
	// エレメント
	//====================================
	SkinElement*		elemSkin;		// 必ず1つ存在する
};


typedef std::vector<ControllerElement*>	VECCONTROLLERELEM;


#endif	//___ControllerElement_h___
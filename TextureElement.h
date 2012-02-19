
#pragma once

#if !defined ___TextureElement_h___
#define ___TextureElement_h___


#include "DomNodeReader.h"

#include "AssetElement.h"
#include "TechniqueElement.h"
#include "ParamElement.h"


// <texture>エレメントの情報を保存するクラス
class TextureElement: public DomNodeReader
{
public:

	TextureElement();
	~TextureElement();


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
	AssetElement*		elemAsset;			// 0または1つ存在する
	VECPARAMELEM		vecElemParam;		// 0以上存在する
	VECTECHNIQUEELEM	vecElemTechnique;	// 0以上存在する
};


typedef std::vector<TextureElement*>	VECTEXTUREELEM;


#endif	//___TextureElement_h___
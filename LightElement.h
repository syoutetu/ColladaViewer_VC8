
#pragma once

#if !defined ___LightElement_h___
#define ___LightElement_h___


#include "DomNodeReader.h"

#include "AssetElement.h"
#include "ParamElement.h"


// <light>エレメントの情報を保存するクラス
class LightElement: public DomNodeReader
{
public:

	enum TYPE {		// typeアトリビュートの種類
		TYPE_AMBIENT,
		TYPE_DIRECTIONAL,
		TYPE_POINT,
		TYPE_SPOT,

		TYPE_Size
	};


	LightElement();
	~LightElement();

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
	TYPE			attrType;	// Optional

	void ReadAttributes(const DOMNode* node);

	void SetType(const XMLCh* type);

	//====================================
	// エレメント
	//====================================
	AssetElement*	elemAsset;			// 0または1つ存在する？
	VECPARAMELEM	vecElemParam;		// 1つ以上存在する
};


typedef std::vector<LightElement*>	VECLIGHTELEM;


#endif	//___LightElement_h___
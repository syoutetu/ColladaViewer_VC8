
#pragma once

#if !defined ___MaterialElement_h___
#define ___MaterialElement_h___


#include "DomNodeReader.h"

#include "AssetElement.h"
#include "ParamElement.h"
#include "ShaderElement.h"


// <material>エレメントの情報を保存するクラス
class MaterialElement: public DomNodeReader
{
public:

	MaterialElement();
	~MaterialElement();

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

	void ReadAttributes(const DOMNode* node);

	//====================================
	// エレメント
	//====================================
	AssetElement*	elemAsset;			// 0または1つ存在する？
	VECPARAMELEM	vecElemParam;		// 0以上存在する
	VECSHADERELEM	vecElemShader;		// 1つ以上存在する
};


typedef std::vector<MaterialElement*>	VECMATERIALELEM;


#endif	//___MaterialElement_h___
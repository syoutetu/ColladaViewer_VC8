
#pragma once

#if !defined ___ShaderElement_h___
#define ___ShaderElement_h___

#include "DomNodeReader.h"

#include "ParamElement.h"
#include "TechniqueElement.h"


// <shader>エレメントの情報を保存するクラス
class ShaderElement: public DomNodeReader
{
public:

	ShaderElement();
	~ShaderElement();

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
	VECPARAMELEM		vecElemParam;		// 0以上存在する
	VECTECHNIQUEELEM	vecElemTechnique;	// 1つ以上存在する
};


typedef std::vector<ShaderElement*>	VECSHADERELEM;


#endif	//___ShaderElement_h___
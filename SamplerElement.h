
#pragma once

#if !defined ___SamplerElement_h___
#define ___SamplerElement_h___


#include "DomNodeReader.h"

#include "InputElement.h"


// <sampler>エレメントの情報を保存するクラス
class SamplerElement: public DomNodeReader
{

public:

	SamplerElement();
	~SamplerElement();

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
	VECINPUTELEM		vecElemInput;			// 1つ以上存在する
};


typedef std::vector<SamplerElement*>	VECSAMPLERELEM;


#endif	//___SamplerElement_h___
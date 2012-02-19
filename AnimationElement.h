
#pragma once

#if !defined ___AnimationElement_h___
#define ___AnimationElement_h___


#include "DomNodeReader.h"

#include "SourceElement.h"
#include "SamplerElement.h"
#include "ChannelElement.h"


// <animation>エレメントの情報を保存するクラス
class AnimationElement: public DomNodeReader
{
public:

	AnimationElement();
	~AnimationElement();


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
	VECSOURCEELEM	vecElemSource;		// 1つ以上存在する
	VECSAMPLERELEM	vecElemSampler;		// 1つ以上存在する
	VECCHANNELELEM	vecElemChannel;		// 1つ以上存在する
};


typedef std::vector<AnimationElement*>	VECANIMATIONELEM;


#endif	//___AnimationElement_h___
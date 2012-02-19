
#pragma once

#if !defined ___ChannelElement_h___
#define ___ChannelElement_h___


#include "DomNodeReader.h"


// <channel>エレメントの情報を保存するクラス
class ChannelElement: public DomNodeReader
{

public:

	ChannelElement();
	~ChannelElement();

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// アトリビュート
	//====================================
	std::wstring	attrId;			// ドキュメント内でUnique, Optional
	std::wstring	attrName;		// Optional
	std::wstring	attrSource;		// Required
	std::wstring	attrTarget;		// Required

	void ReadAttributes(const DOMNode* node);

};


typedef std::vector<ChannelElement*>	VECCHANNELELEM;


#endif	//___ChannelElement_h___
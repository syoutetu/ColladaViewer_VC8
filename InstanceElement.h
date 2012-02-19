
#pragma once

#if !defined ___InstanceElement_h___
#define ___InstanceElement_h___


#include "DomNodeReader.h"


// <instance>エレメントの情報を保存するクラス
class InstanceElement: public DomNodeReader
{

public:

	InstanceElement();
	~InstanceElement();

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// アトリビュート
	//====================================
	std::wstring	attrUrl;		// Required

	void ReadAttributes(const DOMNode* node);

};


typedef std::vector<InstanceElement*>	VECINSTANCEELEM;


#endif	//___InstanceElement_h___
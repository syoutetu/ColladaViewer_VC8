
#pragma once

#if !defined ___BaseValue_h___
#define ___BaseValue_h___


#include "DomNodeReader.h"

#include "ValueElement.h"


// 各種値を持つ要素クラスの基底クラス
class BaseValue: public DomNodeReader
{

public:

	virtual ~BaseValue();

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
//	bool ValidElements(std::wstring& message) const {return false;} 継承クラスで実装する


	unsigned int GetCount() const	{ return (unsigned int)valParam.size(); }

protected:

	BaseValue(unsigned int reqCount);		// インスタンスは作成できない

	bool ValidElements(std::wstring& message, const wchar_t* nodeName) const;

private:

	//====================================
	// アトリビュート
	//====================================
	std::wstring	attrSubId;		// 親の要素内でUnique, Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// ノードの値
	//====================================
	std::vector<float>	valParam;

	void ReadValue(const DOMNode* node);


	const unsigned int requiredCount;	// 必要なノードの値の数
};



#endif	//___BaseValue_h___
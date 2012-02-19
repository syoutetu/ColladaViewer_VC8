
#pragma once

#if !defined ___ArrayElement_h___
#define ___ArrayElement_h___


#include "DomNodeReader.h"


// <array>エレメントの情報を保存するクラス
class ArrayElement: public DomNodeReader
{
public:

	static const int	MIN_INCLUSIVE	= -2147483647 - 1;	// minInclusive属性のデフォルト
	static const int	MAX_INCLUSIVE	= 2147483647;		// maxInclusive属性のデフォルト
	static const int	DIGITS	= 6;						// digits属性のデフォルト
	static const int	MAGNITUDE	= 38;					// magnitude属性のデフォルト



	ArrayElement();
	~ArrayElement();

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// アトリビュート
	//====================================
	unsigned int		attrCount;			// Required
	std::wstring		attrId;				// ドキュメント内でUnique, Optional
	std::wstring		attrName;			// Optional
	std::wstring		attrType;			// Required
	int					attrMinInclusive;	// Optional
	int					attrMaxInclusive;	// Optional
	int					attrDigits;			// Optional
	int					attrMagnitude;		// Optional


	void ReadAttributes(const DOMNode* node);


	//====================================
	// ノードの値(未実装)
	//====================================

};


typedef std::vector<ArrayElement*>	VECARRAYELEM;


#endif	//___ArrayElement_h___
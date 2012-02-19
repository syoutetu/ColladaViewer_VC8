
#pragma once

#if !defined ___IntArrayElement_h___
#define ___IntArrayElement_h___


#include "DomNodeReader.h"


// <int_array>エレメントの情報を保存するクラス
class IntArrayElement: public DomNodeReader
{
public:

	static const int	MIN_INCLUSIVE	= -2147483647 - 1;	// minInclusive属性のデフォルト
	static const int	MAX_INCLUSIVE	= 2147483647;		// maxInclusive属性のデフォルト


	IntArrayElement();
	~IntArrayElement();

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;

	
	unsigned int GetCount() const	{ return (unsigned int)valInt.size(); }
	int GetValue(unsigned int index) const	{ _ASSERTE(index < GetCount()); return valInt[index]; }

	unsigned int GetCountAttribute() const	{ return attrCount; }
	const std::wstring& GetIdAttribute() const	{ return attrId; }
	const std::wstring& GetNameAttribute() const	{ return attrName; }
	int GetMinInclusive() const	{ return attrMinInclusive; }
	int GetMaxInclusive() const	{ return attrMaxInclusive; }

private:

	//====================================
	// アトリビュート
	//====================================
	unsigned int	attrCount;			// Required
	std::wstring	attrId;				// ドキュメント内でUnique, Optional
	std::wstring	attrName;			// Optional
	int				attrMinInclusive;	// Optional
	int				attrMaxInclusive;	// Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// ノードの値
	//====================================
	std::vector<int>		valInt;

	void ReadValue(const DOMNode* node);
};


typedef std::vector<IntArrayElement*>	VECINTAELEM;


#endif	//___IntArrayElement_h___
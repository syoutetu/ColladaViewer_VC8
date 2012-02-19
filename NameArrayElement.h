
#pragma once

#if !defined ___NameArrayElement_h___
#define ___NameArrayElement_h___


#include "DomNodeReader.h"


// <Name_array>エレメントの情報を保存するクラス
class NameArrayElement: public DomNodeReader
{
public:

	NameArrayElement();
	~NameArrayElement();

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	unsigned int GetCount() const	{ return (unsigned int)valName.size(); }

	unsigned int GetCountAttribute() const	{ return attrCount; }
	const std::wstring& GetIdAttribute() const	{ return attrId; }
	const std::wstring& GetNameAttribute() const	{ return attrName; }

private:

	//====================================
	// アトリビュート
	//====================================
	unsigned int	attrCount;		// Required
	std::wstring	attrId;			// ドキュメント内でUnique, Optional
	std::wstring	attrName;		// Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// ノードの値
	//====================================
	std::vector<std::wstring>	valName;

	void ReadValue(const DOMNode* node);
};


typedef std::vector<NameArrayElement*>	VECNAMEAELEM;


#endif	//___NameArrayElement_h___
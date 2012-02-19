
#pragma once

#if !defined ___AccessorElement_h___
#define ___AccessorElement_h___


#include "DomNodeReader.h"

#include "ParamElement.h"


// <accessor>エレメントの情報を保存するクラス
class AccessorElement: public DomNodeReader
{
public:

	AccessorElement();
	~AccessorElement();


	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	const std::wstring& GetIdAttribute() const	{ return attrId; }
	unsigned int GetCountAttribute() const	{ return attrCount; }
	unsigned int GetOffsetAttribute() const	{ return attrOffset; }
	const std::wstring& GetSourceAttribute() const	{ return attrSource; }
	unsigned int GetStrideAttribure() const	{ return attrStride; }

private:

	//====================================
	// アトリビュート
	//====================================
	std::wstring		attrId;			// ドキュメント内でUnique, Optional
	unsigned int		attrCount;		// Required
	unsigned int		attrOffset;		// Optional
	std::wstring		attrSource;		// Required
	unsigned int		attrStride;		// Optional

	void ReadAttributes(const DOMNode* node);
	
	//====================================
	// エレメント
	//====================================
	VECPARAMELEM		vecElemParam;		// 0以上存在する
};


typedef std::vector<AccessorElement*>	VECACCESSORELEM;


#endif	//___AccessorElement_h___

#pragma once

#if !defined ___InputElement_h___
#define ___InputElement_h___


#include "DomNodeReader.h"


// <input>エレメントの情報を保存するクラス
class InputElement: public DomNodeReader
{
public:

	InputElement();
	~InputElement();


	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	unsigned int GetIdxAttribute() const	{ return attrIdx; }
	const std::wstring& GetSemanticAttribute() const	{ return attrSemantic; }
	const std::wstring& GetSourceAttribute() const	{ return attrSource; }

	bool IsPositionSemantic() const	{ return attrSemantic.compare( L"POSITION" ) == 0; }
	bool IsNormalSemantic() const	{ return attrSemantic.compare( L"NORMAL" ) == 0; }
	bool IsTexCoordSemantic() const	{ return attrSemantic.compare( L"TEXCOORD" ) == 0; }

private:

	//====================================
	// アトリビュート
	//====================================
	unsigned int		attrIdx;		// 親の要素が<combiner>または<polygons>などの場合Required
	std::wstring		attrSemantic;	// Required
	std::wstring		attrSource;		// Required

	void ReadAttributes(const DOMNode* node);
};


typedef std::vector<InputElement*>	VECINPUTELEM;


#endif	//___InputElement_h___

#pragma once

#if !defined ___VerticesElement_h___
#define ___VerticesElement_h___


#include "DomNodeReader.h"

#include "InputElement.h"


// <vertices>エレメントの情報を保存するクラス
class VerticesElement: public DomNodeReader
{

public:

	VerticesElement();
	~VerticesElement();


	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	const std::wstring& GetIdAttribute() const	{ return attrId; }
	const std::wstring& GetNameAttribute() const	{ return attrName; }
	unsigned int GetCountAttribute() const	{ return attrCount; }

	unsigned int GetInputCount() const	{ return (unsigned int)vecElemInput.size(); }

	InputElement* GetInputElement(unsigned int index) const	{ _ASSERTE(index < GetInputCount()); return vecElemInput[index]; }
	InputElement* GetInputElementBySemantic(const std::wstring& semantic) const;
	InputElement* GetInputElementOfPositionSemantic() const	{ return GetInputElementBySemantic( L"POSITION" ); }
	InputElement* GetInputElementOfColorSemantic() const	{ return GetInputElementBySemantic( L"COLOR" ); }

private:

	//====================================
	// アトリビュート
	//====================================
	std::wstring		attrId;		// ドキュメント内でUnique, Optional
	std::wstring		attrName;	// Optional
	unsigned int		attrCount;	// Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// エレメント
	//====================================
	VECINPUTELEM		vecElemInput;		// 1つ以上存在する


};


typedef std::vector<VerticesElement*>	VECVERTICESELEM;


#endif	//___VerticesElement_h___

#pragma once

#if !defined ___SourceElement_h___
#define ___SourceElement_h___


#include "DomNodeReader.h"

#include "ArrayElement.h"
#include "BoolArrayElement.h"
#include "FloatArrayElement.h"
#include "IntArrayElement.h"
#include "NameArrayElement.h"
#include "TechniqueElement.h"


// <source>エレメントの情報を保存するクラス
class SourceElement: public DomNodeReader
{
public:

	SourceElement();
	~SourceElement();

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	const std::wstring& GetIdAttribute() const	{ return attrId; }
	const std::wstring& GetNameAttribute() const	{ return attrName; }
	
	unsigned int GetBoolArrayCount() const	{ return (unsigned int)vecElemBoolArray.size(); }
	BoolArrayElement* GetBoolArrayElement(unsigned int index) const	{ _ASSERTE(index < GetBoolArrayCount()); return vecElemBoolArray[index]; }
	BoolArrayElement* GetBoolArrayElement(const AccessorElement* elemAccessor) const;

	unsigned int GetFloatArrayCount() const	{ return (unsigned int)vecElemFloatArray.size(); }
	FloatArrayElement* GetFloatArrayElement(unsigned int index) const	{ _ASSERTE(index < GetFloatArrayCount()); return vecElemFloatArray[index]; }
	FloatArrayElement* GetFloatArrayElement(const AccessorElement* elemAccessor) const;
	
	unsigned int GetIntArrayCount() const	{ return (unsigned int)vecElemIntArray.size(); }
	IntArrayElement* GetIntArrayElement(unsigned int index) const	{ _ASSERTE(index < GetIntArrayCount()); return vecElemIntArray[index]; }
	IntArrayElement* GetIntArrayElement(const AccessorElement* elemAccessor) const;

	TechniqueElement* GetTechniqueOfCommonProfile() const;


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
	VECARRAYELEM		vecElemArray;		// 0以上存在する
	VECBOOLAELEM		vecElemBoolArray;	// 0以上存在する
	VECFLOATAELEM		vecElemFloatArray;	// 0以上存在する
	VECINTAELEM			vecElemIntArray;	// 0以上存在する
	VECNAMEAELEM		vecElemNameArray;	// 0以上存在する
	VECTECHNIQUEELEM	vecElemTechnique;	// 0以上存在する？
};


typedef std::vector<SourceElement*>	VECSOURCEELEM;


#endif	//___SourceElement_h___
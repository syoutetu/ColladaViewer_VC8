
#pragma once

#if !defined ___BasePrimitive_h___
#define ___BasePrimitive_h___


#include "DomNodeReader.h"

#include "InputElement.h"
#include "PrimitiveElement.h"
#include "ParamElement.h"



// 各種プリミティブを持つ要素クラスの基底クラス
class BasePrimitive: public DomNodeReader
{

public:

	virtual ~BasePrimitive();

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
//	bool ValidElements(std::wstring& message) const;	継承クラスで実装する


	unsigned int GetInputCount() const	{ return (unsigned int)vecElemInput.size(); }
	InputElement* GetInputElement(unsigned int index) const	{ _ASSERTE(index < GetInputCount()); return vecElemInput[index]; }
	InputElement* GetInputElementByAttrIdx(unsigned int idx) const;	// idxアトリビュートを指定して取得する

	unsigned int GetParamCount() const	{ return (unsigned int)vecElemParam.size(); }
	
	unsigned int GetPrimitiveCount() const	{ return (unsigned int)vecElemP.size(); }
	PrimitiveElement* GetPrimitiveElement(unsigned int index) const	{ _ASSERTE(index < GetPrimitiveCount()); return vecElemP[index]; }

protected:

	BasePrimitive();		// インスタンスは作成できない

	bool ValidElements(std::wstring& message, const wchar_t* nodeName) const;

private:

	//====================================
	// アトリビュート
	//====================================
	unsigned int	attrCount;		// Required
	std::wstring	attrMaterial;	// Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// エレメント
	//====================================
	VECINPUTELEM	vecElemInput;		// 0以上存在する
	VECPARAMELEM	vecElemParam;		// 0以上存在する
	VECPRIMITIVEELEM	vecElemP;		// 0以上存在する
};



#endif	//___BasePrimitive_h___
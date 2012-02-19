
#pragma once

#if !defined ___TechniqueElement_h___
#define ___TechniqueElement_h___


#include "DomNodeReader.h"

#include "AssetElement.h"
#include "AccessorElement.h"
#include "CombinerElement.h"
#include "ImagerElement.h"
#include "InputElement.h"
#include "JointsElement.h"
class OpticsElement; //#include "OpticsElement.h"	相互参照を回避する為にソース側でインクルードする
#include "ParamElement.h"
#include "PassElement.h"
#include "ProgramElement.h"



// <technique>エレメントの情報を保存するクラス
class TechniqueElement: public DomNodeReader
{
public:

	TechniqueElement();
	~TechniqueElement();

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	unsigned int GetAccessorCount() const	{ return (unsigned int)vecElemAccessor.size(); }
	AccessorElement* GetAccessorElement(unsigned int index) const	{ _ASSERTE(index < GetAccessorCount()); return vecElemAccessor[index]; }

	const std::wstring& GetProfileAttribute() const	{ return attrProfile; }


private:

	//====================================
	// アトリビュート
	//====================================
	std::wstring	attrProfile;		// Required

	void ReadAttributes(const DOMNode* node);

	//====================================
	// エレメント
	//====================================
	AssetElement*		elemAsset;			// 0または1つ存在する
	VECACCESSORELEM		vecElemAccessor;	// 0以上存在する
	CombinerElement*	elemCombiner;		// 0または1つ存在する(<source>の子ノードの場合だけ)
	JointsElement*		elemJoints;			// 0または1つ存在する(<source>の子ノードの場合だけ)
	OpticsElement*		elemOptics;			// 必ず1つ存在する(<camera>の子ノードの場合だけ)
	ImagerElement*		elemImager;			// 0以上存在する(<camera>の子ノードの場合だけ)
	VECINPUTELEM		vecElemInput;		// 0以上存在する(<texture>の子ノードの場合だけ)
	VECPARAMELEM		vecElemParam;		// 0以上存在する(<camera>の子ノードの場合以外)
	VECPASSELEM			vecElemPass;		// 0以上存在する(<shader>の子ノードの場合だけ)
	ProgramElement*		elemProgram;		// 0または1つ存在する(<shader>,<source>,<texture>の子ノードの場合だけ)
};


typedef std::vector<TechniqueElement*>	VECTECHNIQUEELEM;


#endif	//___TechniqueElement_h___
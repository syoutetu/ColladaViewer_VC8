
#pragma once

#if !defined ___ParamElement_h___
#define ___ParamElement_h___


#include "DomNodeReader.h"


// <param>エレメントの情報を保存するクラス
class ParamElement: public DomNodeReader
{
public:

	enum FLOW {		// flowアトリビュートの種類
		FLOW_Null,

		FLOW_IN,
		FLOW_OUT,
		FLOW_INOUT,
	};

	enum TYPE {		// typeアトリビュートの種類
		TYPE_Null,

		TYPE_BOOL,		// bool

		TYPE_FLOAT,		// float
		TYPE_FLOAT2,
		TYPE_FLOAT3,
		TYPE_FLOAT4,
		TYPE_FLOAT_End,	// floatの終端(判定の為)

		TYPE_BLEND,		// blend
		TYPE_FUNCTION,	// function
	};


	ParamElement();
	~ParamElement();

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	bool IsInFlow() const	{ return attrFlow == FLOW_IN; }
	bool IsOutFlow() const	{ return attrFlow == FLOW_OUT; }
	bool IsInOutFlow() const	{ return attrFlow == FLOW_INOUT; }

	bool IsBoolType() const	{ return attrType == TYPE_BOOL; }
	bool IsFloatType() const	{ return attrType >= TYPE_FLOAT && attrType <= TYPE_FLOAT_End; }
	bool IsBlendType() const	{ return attrType == TYPE_BLEND; }
	bool IsFunctionType() const	{ return attrType == TYPE_FUNCTION; }

	unsigned int GetSize() const;
	bool GetParamB(unsigned int index) const	{ if( valBool.size() >= index ) { return false; } return valBool[index]; }
	float GetParamF(unsigned int index) const	{ if( valFloat.size() >= index ) { return 0.0f; } return valFloat[index]; }

private:

	//====================================
	// アトリビュート
	//====================================
	std::wstring	attrId;			// ドキュメント内でUnique, Optional
	std::wstring	attrName;		// Optional
	FLOW			attrFlow;		// Optional
	std::wstring	attrSemantic;	// Optional
	TYPE			attrType;		// Required
	std::wstring	attrSubId;		// Optional

	void ReadAttributes(const DOMNode* node);

	void SetFlow(const XMLCh* flow);
	void SetType(const XMLCh* type);


	//====================================
	// ノードの値
	//====================================
	std::vector<bool>	valBool;
	std::vector<float>	valFloat;
	
	void ReadValue(const DOMNode* node);
};


typedef std::vector<ParamElement*>	VECPARAMELEM;


#endif	//___ParamElement_h___
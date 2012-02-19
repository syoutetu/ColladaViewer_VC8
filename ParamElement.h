
#pragma once

#if !defined ___ParamElement_h___
#define ___ParamElement_h___


#include "DomNodeReader.h"


// <param>�G�������g�̏���ۑ�����N���X
class ParamElement: public DomNodeReader
{
public:

	enum FLOW {		// flow�A�g���r���[�g�̎��
		FLOW_Null,

		FLOW_IN,
		FLOW_OUT,
		FLOW_INOUT,
	};

	enum TYPE {		// type�A�g���r���[�g�̎��
		TYPE_Null,

		TYPE_BOOL,		// bool

		TYPE_FLOAT,		// float
		TYPE_FLOAT2,
		TYPE_FLOAT3,
		TYPE_FLOAT4,
		TYPE_FLOAT_End,	// float�̏I�[(����̈�)

		TYPE_BLEND,		// blend
		TYPE_FUNCTION,	// function
	};


	ParamElement();
	~ParamElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
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
	// �A�g���r���[�g
	//====================================
	std::wstring	attrId;			// �h�L�������g����Unique, Optional
	std::wstring	attrName;		// Optional
	FLOW			attrFlow;		// Optional
	std::wstring	attrSemantic;	// Optional
	TYPE			attrType;		// Required
	std::wstring	attrSubId;		// Optional

	void ReadAttributes(const DOMNode* node);

	void SetFlow(const XMLCh* flow);
	void SetType(const XMLCh* type);


	//====================================
	// �m�[�h�̒l
	//====================================
	std::vector<bool>	valBool;
	std::vector<float>	valFloat;
	
	void ReadValue(const DOMNode* node);
};


typedef std::vector<ParamElement*>	VECPARAMELEM;


#endif	//___ParamElement_h___
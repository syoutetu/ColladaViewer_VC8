
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


// <source>�G�������g�̏���ۑ�����N���X
class SourceElement: public DomNodeReader
{
public:

	SourceElement();
	~SourceElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
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
	// �A�g���r���[�g
	//====================================
	std::wstring	attrId;		// �h�L�������g����Unique, Optional
	std::wstring	attrName;	// Optional

	void ReadAttributes(const DOMNode* node);

	//====================================
	// �G�������g
	//====================================
	VECARRAYELEM		vecElemArray;		// 0�ȏ㑶�݂���
	VECBOOLAELEM		vecElemBoolArray;	// 0�ȏ㑶�݂���
	VECFLOATAELEM		vecElemFloatArray;	// 0�ȏ㑶�݂���
	VECINTAELEM			vecElemIntArray;	// 0�ȏ㑶�݂���
	VECNAMEAELEM		vecElemNameArray;	// 0�ȏ㑶�݂���
	VECTECHNIQUEELEM	vecElemTechnique;	// 0�ȏ㑶�݂���H
};


typedef std::vector<SourceElement*>	VECSOURCEELEM;


#endif	//___SourceElement_h___
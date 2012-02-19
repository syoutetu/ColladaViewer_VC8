
#pragma once

#if !defined ___AccessorElement_h___
#define ___AccessorElement_h___


#include "DomNodeReader.h"

#include "ParamElement.h"


// <accessor>�G�������g�̏���ۑ�����N���X
class AccessorElement: public DomNodeReader
{
public:

	AccessorElement();
	~AccessorElement();


	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
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
	// �A�g���r���[�g
	//====================================
	std::wstring		attrId;			// �h�L�������g����Unique, Optional
	unsigned int		attrCount;		// Required
	unsigned int		attrOffset;		// Optional
	std::wstring		attrSource;		// Required
	unsigned int		attrStride;		// Optional

	void ReadAttributes(const DOMNode* node);
	
	//====================================
	// �G�������g
	//====================================
	VECPARAMELEM		vecElemParam;		// 0�ȏ㑶�݂���
};


typedef std::vector<AccessorElement*>	VECACCESSORELEM;


#endif	//___AccessorElement_h___
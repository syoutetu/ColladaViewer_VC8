
#pragma once

#if !defined ___ProgramElement_h___
#define ___ProgramElement_h___


#include "DomNodeReader.h"

#include "AssetElement.h"
#include "CodeElement.h"
#include "EntryElement.h"
#include "ParamElement.h"


// <program>�G�������g�̏���ۑ�����N���X
class ProgramElement
{
public:

	ProgramElement();
	~ProgramElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// �A�g���r���[�g
	//====================================
	std::wstring		attrId;		// �h�L�������g����Unique, Optional
	std::wstring		attrName;	// Optional
	std::wstring		attrUrl;	// Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// �G�������g
	//====================================
	AssetElement*		elemAsset;		// 0�܂���1���݂���H
	CodeElement*		elemCode;		// 0�܂���1���݂���
	EntryElement*		elemEntry;		// 0�܂���1���݂���H
	VECPARAMELEM		vecElemParam;	// 0�ȏ㑶�݂���
};


typedef std::vector<ProgramElement*>	VECPROGRAMELEM;


#endif	//___ProgramElement_h___
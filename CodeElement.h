
#pragma once

#if !defined ___CodeElement_h___
#define ___CodeElement_h___


#include "DomNodeReader.h"


// <code>�G�������g�̏���ۑ�����N���X
class CodeElement: public DomNodeReader
{
public:

	CodeElement();
	~CodeElement();


	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// �A�g���r���[�g
	//====================================
	std::wstring		attrId;			// �h�L�������g����Unique, Optional
	std::wstring		attrLang;		// Required
	std::wstring		attrProfile;	// Optional
	std::wstring		attrSemantic;	// Optional
	std::wstring		attrUrl;		// Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// �m�[�h�̒l
	//====================================
	std::wstring		valCode;

	void ReadValue(const DOMNode* node);
};


typedef std::vector<CodeElement*>	VECCODEELEM;


#endif	//___CodeElement_h___
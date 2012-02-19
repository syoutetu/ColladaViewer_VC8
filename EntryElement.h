
#pragma once

#if !defined ___EntryElement_h___
#define ___EntryElement_h___


#include "DomNodeReader.h"

#include "ParamElement.h"


// <entry>�G�������g�̏���ۑ�����N���X
class EntryElement: public DomNodeReader
{
public:

	EntryElement();
	~EntryElement();


	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// �A�g���r���[�g
	//====================================
	std::wstring		attrFunction;	// Required
	std::wstring		attrSemantic;	// Optional
	
	void ReadAttributes(const DOMNode* node);


	//====================================
	// �G�������g
	//====================================
	VECPARAMELEM		vecElemParam;	// 0�ȏ㑶�݂���
};


typedef std::vector<EntryElement*>	VECENTRYELEM;


#endif	//___EntryElement_h___
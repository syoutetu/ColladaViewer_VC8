
#pragma once

#if !defined ___SkinElement_h___
#define ___SkinElement_h___


#include "DomNodeReader.h"

#include "SourceElement.h"
#include "VerticesElement.h"


// <skin>�G�������g�̏���ۑ�����N���X
class SkinElement: public DomNodeReader
{
public:

	SkinElement();
	~SkinElement();


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

	void ReadAttributes(const DOMNode* node);


	//====================================
	// �G�������g
	//====================================
	VECSOURCEELEM		vecElemSource;		// 1�ȏ㑶�݂���
	VerticesElement*	elemVertices;		// �K��1���݂���
};


typedef std::vector<SkinElement*>	VECSKINELEM;


#endif	//___SkinElement_h___
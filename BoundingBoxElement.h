
#pragma once

#if !defined ___BoundingBoxElement_h___
#define ___BoundingBoxElement_h___


#include "DomNodeReader.h"

#include "MinElement.h"
#include "MaxElement.h"


// <boundingbox>�G�������g�̏���ۑ�����N���X
class BoundingBoxElement: public DomNodeReader
{

public:

	BoundingBoxElement();
	~BoundingBoxElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// �A�g���r���[�g
	//====================================
	std::wstring	attrSubId;		// �e�̗v�f����Unique, Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// �G�������g
	//====================================
	MinElement*		elemMin;		// �K��1���݂���
	MaxElement*		elemMax;		// �K��1���݂���

};


typedef std::vector<BoundingBoxElement*>	VECBOUNDINGBOXELEM;


#endif	//___BoundingBoxElement_h___
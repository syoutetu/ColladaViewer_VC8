
#pragma once

#if !defined ___ControllerElement_h___
#define ___ControllerElement_h___


#include "DomNodeReader.h"

#include "SkinElement.h"


// <controller>�G�������g�̏���ۑ�����N���X
class ControllerElement: public DomNodeReader
{
public:

	ControllerElement();
	~ControllerElement();


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
	std::wstring		attrName;		// Optional
	std::wstring		attrTarget;		// Required

	void ReadAttributes(const DOMNode* node);


	//====================================
	// �G�������g
	//====================================
	SkinElement*		elemSkin;		// �K��1���݂���
};


typedef std::vector<ControllerElement*>	VECCONTROLLERELEM;


#endif	//___ControllerElement_h___
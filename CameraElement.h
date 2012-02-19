
#pragma once

#if !defined ___CameraElement_h___
#define ___CameraElement_h___


#include "DomNodeReader.h"

#include "TechniqueElement.h"


// <camera>�G�������g�̏���ۑ�����N���X
class CameraElement: public DomNodeReader
{
public:

	CameraElement();
	~CameraElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


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
	VECTECHNIQUEELEM	vecElemTechnique;		// 1�ȏ㑶�݂���
};


typedef std::vector<CameraElement*>	VECCAMERAELEM;


#endif	//___CameraElement_h___
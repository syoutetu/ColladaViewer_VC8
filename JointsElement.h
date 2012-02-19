
#pragma once

#if !defined ___JointsElement_h___
#define ___JointsElement_h___


#include "DomNodeReader.h"

#include "InputElement.h"


// <joints>�G�������g�̏���ۑ�����N���X
class JointsElement: public DomNodeReader
{

public:

	JointsElement();
	~JointsElement();

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
	unsigned int	attrCount;	// Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// �G�������g
	//====================================
	VECINPUTELEM		vecElemInput;		// 2�ȏ㑶�݂���

};


typedef std::vector<JointsElement*>	VECJOINTSELEM;


#endif	//___JointsElement_h___
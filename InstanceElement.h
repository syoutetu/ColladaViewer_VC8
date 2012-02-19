
#pragma once

#if !defined ___InstanceElement_h___
#define ___InstanceElement_h___


#include "DomNodeReader.h"


// <instance>�G�������g�̏���ۑ�����N���X
class InstanceElement: public DomNodeReader
{

public:

	InstanceElement();
	~InstanceElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// �A�g���r���[�g
	//====================================
	std::wstring	attrUrl;		// Required

	void ReadAttributes(const DOMNode* node);

};


typedef std::vector<InstanceElement*>	VECINSTANCEELEM;


#endif	//___InstanceElement_h___

#pragma once

#if !defined ___ChannelElement_h___
#define ___ChannelElement_h___


#include "DomNodeReader.h"


// <channel>�G�������g�̏���ۑ�����N���X
class ChannelElement: public DomNodeReader
{

public:

	ChannelElement();
	~ChannelElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// �A�g���r���[�g
	//====================================
	std::wstring	attrId;			// �h�L�������g����Unique, Optional
	std::wstring	attrName;		// Optional
	std::wstring	attrSource;		// Required
	std::wstring	attrTarget;		// Required

	void ReadAttributes(const DOMNode* node);

};


typedef std::vector<ChannelElement*>	VECCHANNELELEM;


#endif	//___ChannelElement_h___
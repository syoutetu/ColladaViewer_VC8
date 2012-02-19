
#pragma once

#if !defined ___AnimationElement_h___
#define ___AnimationElement_h___


#include "DomNodeReader.h"

#include "SourceElement.h"
#include "SamplerElement.h"
#include "ChannelElement.h"


// <animation>�G�������g�̏���ۑ�����N���X
class AnimationElement: public DomNodeReader
{
public:

	AnimationElement();
	~AnimationElement();


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
	VECSOURCEELEM	vecElemSource;		// 1�ȏ㑶�݂���
	VECSAMPLERELEM	vecElemSampler;		// 1�ȏ㑶�݂���
	VECCHANNELELEM	vecElemChannel;		// 1�ȏ㑶�݂���
};


typedef std::vector<AnimationElement*>	VECANIMATIONELEM;


#endif	//___AnimationElement_h___
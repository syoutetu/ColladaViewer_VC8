
#pragma once

#if !defined ___ImageElement_h___
#define ___ImageElement_h___


#include "DomNodeReader.h"


// <image>�G�������g�̏���ۑ�����N���X
class ImageElement: public DomNodeReader
{
public:

	ImageElement();
	~ImageElement();


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
	std::wstring		attrSource;		// Optional
	std::wstring		attrFormat;		// Optional
	unsigned int		attrHeight;		// Optional
	unsigned int		attrWidth;		// Optional
	unsigned int		attrDepth;		// Optional

	void ReadAttributes(const DOMNode* node);
};


typedef std::vector<ImageElement*>	VECIMAGEELEM;


#endif	//___ImageElement_h___
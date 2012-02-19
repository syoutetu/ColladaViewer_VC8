
#pragma once

#if !defined ___TextureElement_h___
#define ___TextureElement_h___


#include "DomNodeReader.h"

#include "AssetElement.h"
#include "TechniqueElement.h"
#include "ParamElement.h"


// <texture>�G�������g�̏���ۑ�����N���X
class TextureElement: public DomNodeReader
{
public:

	TextureElement();
	~TextureElement();


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
	AssetElement*		elemAsset;			// 0�܂���1���݂���
	VECPARAMELEM		vecElemParam;		// 0�ȏ㑶�݂���
	VECTECHNIQUEELEM	vecElemTechnique;	// 0�ȏ㑶�݂���
};


typedef std::vector<TextureElement*>	VECTEXTUREELEM;


#endif	//___TextureElement_h___

#pragma once

#if !defined ___MaterialElement_h___
#define ___MaterialElement_h___


#include "DomNodeReader.h"

#include "AssetElement.h"
#include "ParamElement.h"
#include "ShaderElement.h"


// <material>�G�������g�̏���ۑ�����N���X
class MaterialElement: public DomNodeReader
{
public:

	MaterialElement();
	~MaterialElement();

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
	AssetElement*	elemAsset;			// 0�܂���1���݂���H
	VECPARAMELEM	vecElemParam;		// 0�ȏ㑶�݂���
	VECSHADERELEM	vecElemShader;		// 1�ȏ㑶�݂���
};


typedef std::vector<MaterialElement*>	VECMATERIALELEM;


#endif	//___MaterialElement_h___
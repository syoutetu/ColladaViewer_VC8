
#pragma once

#if !defined ___LightElement_h___
#define ___LightElement_h___


#include "DomNodeReader.h"

#include "AssetElement.h"
#include "ParamElement.h"


// <light>�G�������g�̏���ۑ�����N���X
class LightElement: public DomNodeReader
{
public:

	enum TYPE {		// type�A�g���r���[�g�̎��
		TYPE_AMBIENT,
		TYPE_DIRECTIONAL,
		TYPE_POINT,
		TYPE_SPOT,

		TYPE_Size
	};


	LightElement();
	~LightElement();

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
	TYPE			attrType;	// Optional

	void ReadAttributes(const DOMNode* node);

	void SetType(const XMLCh* type);

	//====================================
	// �G�������g
	//====================================
	AssetElement*	elemAsset;			// 0�܂���1���݂���H
	VECPARAMELEM	vecElemParam;		// 1�ȏ㑶�݂���
};


typedef std::vector<LightElement*>	VECLIGHTELEM;


#endif	//___LightElement_h___
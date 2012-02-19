
#pragma once

#if !defined ___TechniqueElement_h___
#define ___TechniqueElement_h___


#include "DomNodeReader.h"

#include "AssetElement.h"
#include "AccessorElement.h"
#include "CombinerElement.h"
#include "ImagerElement.h"
#include "InputElement.h"
#include "JointsElement.h"
class OpticsElement; //#include "OpticsElement.h"	���ݎQ�Ƃ��������ׂɃ\�[�X���ŃC���N���[�h����
#include "ParamElement.h"
#include "PassElement.h"
#include "ProgramElement.h"



// <technique>�G�������g�̏���ۑ�����N���X
class TechniqueElement: public DomNodeReader
{
public:

	TechniqueElement();
	~TechniqueElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	unsigned int GetAccessorCount() const	{ return (unsigned int)vecElemAccessor.size(); }
	AccessorElement* GetAccessorElement(unsigned int index) const	{ _ASSERTE(index < GetAccessorCount()); return vecElemAccessor[index]; }

	const std::wstring& GetProfileAttribute() const	{ return attrProfile; }


private:

	//====================================
	// �A�g���r���[�g
	//====================================
	std::wstring	attrProfile;		// Required

	void ReadAttributes(const DOMNode* node);

	//====================================
	// �G�������g
	//====================================
	AssetElement*		elemAsset;			// 0�܂���1���݂���
	VECACCESSORELEM		vecElemAccessor;	// 0�ȏ㑶�݂���
	CombinerElement*	elemCombiner;		// 0�܂���1���݂���(<source>�̎q�m�[�h�̏ꍇ����)
	JointsElement*		elemJoints;			// 0�܂���1���݂���(<source>�̎q�m�[�h�̏ꍇ����)
	OpticsElement*		elemOptics;			// �K��1���݂���(<camera>�̎q�m�[�h�̏ꍇ����)
	ImagerElement*		elemImager;			// 0�ȏ㑶�݂���(<camera>�̎q�m�[�h�̏ꍇ����)
	VECINPUTELEM		vecElemInput;		// 0�ȏ㑶�݂���(<texture>�̎q�m�[�h�̏ꍇ����)
	VECPARAMELEM		vecElemParam;		// 0�ȏ㑶�݂���(<camera>�̎q�m�[�h�̏ꍇ�ȊO)
	VECPASSELEM			vecElemPass;		// 0�ȏ㑶�݂���(<shader>�̎q�m�[�h�̏ꍇ����)
	ProgramElement*		elemProgram;		// 0�܂���1���݂���(<shader>,<source>,<texture>�̎q�m�[�h�̏ꍇ����)
};


typedef std::vector<TechniqueElement*>	VECTECHNIQUEELEM;


#endif	//___TechniqueElement_h___

#pragma once

#if !defined ___SceneElement_h___
#define ___SceneElement_h___


#include "DomNodeReader.h"

#include "LookatElement.h"
#include "MatrixElement.h"
#include "PerspectiveElement.h"
#include "RotateElement.h"
#include "ScaleElement.h"
#include "SkewElement.h"
#include "TranslateElement.h"
#include "BoundingBoxElement.h"
#include "NodeElement.h"
#include "ExtraElement.h"


// <scene>�G�������g�̏���ۑ�����N���X
class SceneElement: public DomNodeReader
{
public:

	SceneElement();
	~SceneElement();


	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;

private:

	//====================================
	// �A�g���r���[�g
	//====================================
	std::wstring	attrId;		// Optional
	std::wstring	attrName;	// Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// �G�������g
	//====================================
	VECLOOKATELEM		vecElemLookat;		// 0�ȏ㑶�݂���
	VECMATRIXELEM		vecElemMatrix;		// 0�ȏ㑶�݂���
	VECPERSPECTIVEELEM	vecElemPerspective;	// 0�ȏ㑶�݂���
	VECROTATEELEM		vecElemRotate;		// 0�ȏ㑶�݂���
	VECSCALEELEM		vecElemScale;		// 0�ȏ㑶�݂���
	VECSKEWELEM			vecElemSkew;		// 0�ȏ㑶�݂���
	VECTRANSLATEELEM	vecElemTranslate;	// 0�ȏ㑶�݂���
	VECBOUNDINGBOXELEM	vecElemBoundingBox;	// 0�ȏ㑶�݂���
	VECNODEELEM			vecElemNode;		// 0�ȏ㑶�݂���
	VECEXTRAELEM		vecElemExtra;		// 0�ȏ㑶�݂���
};


typedef std::vector<SceneElement*>	VECSCENEELEM;


#endif	//___SceneElement_h___
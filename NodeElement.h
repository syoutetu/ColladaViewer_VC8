
#pragma once

#if !defined ___NodeElement_h___
#define ___NodeElement_h___


#include "DomNodeReader.h"

#include "LookatElement.h"
#include "MatrixElement.h"
#include "PerspectiveElement.h"
#include "RotateElement.h"
#include "ScaleElement.h"
#include "SkewElement.h"
#include "TranslateElement.h"
#include "BoundingBoxElement.h"
#include "InstanceElement.h"
#include "ExtraElement.h"


class NodeElement;
typedef std::vector<NodeElement*>	VECNODEELEM;


// <node>�G�������g�̏���ۑ�����N���X
class NodeElement: public DomNodeReader
{

public:

	enum TYPE {
		TYPE_JOINT,
		TYPE_NODE,

		TYPE_Size
	};


	NodeElement();
	~NodeElement();

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
	VECLOOKATELEM		vecElemLookat;			// 0�ȏ㑶�݂���
	VECMATRIXELEM		vecElemMatrix;			// 0�ȏ㑶�݂���
	VECPERSPECTIVEELEM	vecElemPerspective;		// 0�ȏ㑶�݂���
	VECROTATEELEM		vecElemRotate;			// 0�ȏ㑶�݂���
	VECSCALEELEM		vecElemScale;			// 0�ȏ㑶�݂���
	VECSKEWELEM			vecElemSkew;			// 0�ȏ㑶�݂���
	VECTRANSLATEELEM	vecElemTranslate;		// 0�ȏ㑶�݂���
	VECBOUNDINGBOXELEM	vecElemBoundingBox;		// 0�ȏ㑶�݂���
	VECINSTANCEELEM		vecElemInstance;		// 0�ȏ㑶�݂���
	VECNODEELEM			vecElemNode;			// 0�ȏ㑶�݂���
	VECEXTRAELEM		vecElemExtra;			// 0�ȏ㑶�݂���

};


#endif	//___NodeElement_h___
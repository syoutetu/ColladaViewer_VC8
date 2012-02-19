
#pragma once

#if !defined ___GeometryElement_h___
#define ___GeometryElement_h___


#include "DomNodeReader.h"

#include "MeshElement.h"
#include "ExtraElement.h"


// <geometry>�G�������g�̏���ۑ�����N���X
class GeometryElement: public DomNodeReader
{

public:

	GeometryElement();
	~GeometryElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	MeshElement* GetMeshElement() const	{ return elemMesh; }
	
	unsigned int GetExtraCount() const	{ return (unsigned int)vecElemExtra.size(); }
	ExtraElement* GetExtraElement(unsigned int index) const	{ _ASSERTE(index < GetExtraCount()); return vecElemExtra[index]; }

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
	MeshElement*	elemMesh;			// �K��1���݂���
	VECEXTRAELEM	vecElemExtra;		// 0�ȏ㑶�݂���
};


typedef std::vector<GeometryElement*>	VECGEOMETRYELEM;


#endif	//___GeometryElement_h___
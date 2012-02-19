
#pragma once

#if !defined ___MeshElement_h___
#define ___MeshElement_h___


#include "DomNodeReader.h"

#include "SourceElement.h"
#include "VerticesElement.h"
#include "LinesElement.h"
#include "LinestripsElement.h"
#include "PolygonsElement.h"
#include "TrianglesElement.h"
#include "TrifansElement.h"
#include "TristripsElement.h"


// <mesh>�G�������g�̏���ۑ�����N���X
class MeshElement: public DomNodeReader
{

public:

	MeshElement();
	~MeshElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	unsigned int GetSourceCount() const	{ return (unsigned int)vecElemSource.size(); }
	SourceElement* GetSourceElement(unsigned int index) const	{ _ASSERTE(index < GetSourceCount()); return vecElemSource[index]; }
	SourceElement* GetSourceElementById(const std::wstring& id) const;

	VerticesElement* GetVerticesElement() const	{ return elemVertices; }

	unsigned int GetLinesCount() const	{ return (unsigned int)vecElemLines.size(); }
	LinesElement* GetLinesElement(unsigned int index) const	{ _ASSERTE(index < GetLinesCount()); return vecElemLines[index]; }

	unsigned int GetLinestripsCount() const	{ return (unsigned int)vecElemLinestrips.size(); }
	LinestripsElement* GetLinestripsElement(unsigned int index) const	{ _ASSERTE(index < GetLinestripsCount()); return vecElemLinestrips[index]; }

	unsigned int GetPolygonsCount() const	{ return (unsigned int)vecElemPolygons.size(); }
	PolygonsElement* GetPolygonsElement(unsigned int index) const	{ _ASSERTE(index < GetPolygonsCount()); return vecElemPolygons[index]; }

	unsigned int GetTrianglesCount() const	{ return (unsigned int)vecElemTriangles.size(); }
	TrianglesElement* GetTrianglesElement(unsigned int index) const	{ _ASSERTE(index < GetTrianglesCount()); return vecElemTriangles[index]; }

	unsigned int GetTrifansCount() const	{ return (unsigned int)vecElemTrifans.size(); }
	TrifansElement* GetTrifansElement(unsigned int index) const	{ _ASSERTE(index < GetTrifansCount()); return vecElemTrifans[index]; }

	unsigned int GetTristripsCount() const	{ return (unsigned int)vecElemTristrips.size(); }
	TristripsElement* GetTristripsElement(unsigned int index) const	{ _ASSERTE(index < GetTristripsCount()); return vecElemTristrips[index]; }


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
	VECSOURCEELEM		vecElemSource;		// 1�ȏ㑶�݂���
	VerticesElement*	elemVertices;		// �K��1���݂���
	VECLINESELEM		vecElemLines;		// 0�ȏ㑶�݂���
	VECLINESTRIPSELEM	vecElemLinestrips;	// 0�ȏ㑶�݂���
	VECPOLYGONSELEM		vecElemPolygons;	// 0�ȏ㑶�݂���
	VECTRIANGLESELEM	vecElemTriangles;	// 0�ȏ㑶�݂���
	VECTRIFANSELEM		vecElemTrifans;		// 0�ȏ㑶�݂���
	VECTRISTRIPSELEM	vecElemTristrips;	// 0�ȏ㑶�݂���


public:

	enum PRIM_TYPE {	// �v���~�e�B�u�̎��
		PRIM_TYPE_LINES,
		PRIM_TYPE_LINESTRIPS,
		PRIM_TYPE_POLYGONS,
		PRIM_TYPE_TRIANGLES,
		PRIM_TYPE_TRIFANS,
		PRIM_TYPE_TRISTRIPS,

		PRIM_TYPE_Size
	};


	void GetAllInputElement(const BasePrimitive* elemPrim, VECINPUTELEM& elemInput, bool includeVertices) const;

	bool CreateTriangleList(unsigned int& vertexCount, float*& vertexData, PRIM_TYPE primType, unsigned int primIndex) const;
	bool CreateTriangleList(unsigned int& vertexCount, float*& vertexData) const;

private:

	typedef std::vector<unsigned int>	VECUINT;

	bool IsVerticesElementReference(const InputElement* elemInput) const;
	bool IsVerticesElementReference(const std::wstring& id) const;
	unsigned int GetCommonTechniqueAccessorStride(const SourceElement* elemSource) const;
	bool FindInputSource(const BasePrimitive* elemPrim, VECUINT& vecSourceCount, VECSOURCEELEM& vecSource, unsigned int& vertexStride) const;

	bool CreateTriangleListFromPolygons(unsigned int& vertexCount, float*& vertexData, unsigned int primIndex) const;
	bool CreateTriangleListFromTriangles(unsigned int& vertexCount, float*& vertexData, unsigned int primIndex) const;
	bool CreateTriangleListFromTrifans(unsigned int& vertexCount, float*& vertexData, unsigned int primIndex) const;
	bool CreateTriangleListFromTristrips(unsigned int& vertexCount, float*& vertexData, unsigned int primIndex) const;
};


typedef std::vector<MeshElement*>	VECMESHELEM;


#endif	//___MeshElement_h___
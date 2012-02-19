
#pragma once

#if !defined ___GeometryElement_h___
#define ___GeometryElement_h___


#include "DomNodeReader.h"

#include "MeshElement.h"
#include "ExtraElement.h"


// <geometry>エレメントの情報を保存するクラス
class GeometryElement: public DomNodeReader
{

public:

	GeometryElement();
	~GeometryElement();

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	MeshElement* GetMeshElement() const	{ return elemMesh; }
	
	unsigned int GetExtraCount() const	{ return (unsigned int)vecElemExtra.size(); }
	ExtraElement* GetExtraElement(unsigned int index) const	{ _ASSERTE(index < GetExtraCount()); return vecElemExtra[index]; }

private:

	//====================================
	// アトリビュート
	//====================================
	std::wstring	attrId;		// ドキュメント内でUnique, Optional
	std::wstring	attrName;	// Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// エレメント
	//====================================
	MeshElement*	elemMesh;			// 必ず1つ存在する
	VECEXTRAELEM	vecElemExtra;		// 0以上存在する
};


typedef std::vector<GeometryElement*>	VECGEOMETRYELEM;


#endif	//___GeometryElement_h___
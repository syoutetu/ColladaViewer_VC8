
#pragma once

#if !defined ___GeometryLibrary_h___
#define ___GeometryLibrary_h___

#include "LibraryElement.h"
#include "GeometryElement.h"


// typeアトリビュートがGEOMETRYの<library>エレメントの情報を保存するクラス
class GeometryLibrary: public LibraryElement
{

public:

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	GeometryLibrary();
	~GeometryLibrary();

	unsigned int GetCount() const	{ return (unsigned int)vecElemGeometry.size(); }
	
	void* GetElement(unsigned int index) const	{ _ASSERTE(index < GetCount()); return vecElemGeometry[index]; }

private:

	VECGEOMETRYELEM	vecElemGeometry;
};


#endif	//___GeometryLibrary_h___
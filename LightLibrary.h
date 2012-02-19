
#pragma once

#if !defined ___LightLibrary_h___
#define ___LightLibrary_h___

#include "LibraryElement.h"
#include "LightElement.h"


// typeアトリビュートがLIGHTの<library>エレメントの情報を保存するクラス
class LightLibrary: public LibraryElement
{

public:

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	LightLibrary();
	~LightLibrary();

	unsigned int GetCount() const	{ return (unsigned int)vecElemLight.size(); }

	void* GetElement(unsigned int index) const	{ _ASSERTE(index < GetCount()); return vecElemLight[index]; }

private:

	VECLIGHTELEM	vecElemLight;
};


#endif	//___LightLibrary_h___
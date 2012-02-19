
#pragma once

#if !defined ___TextureLibrary_h___
#define ___TextureLibrary_h___

#include "LibraryElement.h"
#include "TextureElement.h"


// typeアトリビュートがTEXTUREの<library>エレメントの情報を保存するクラス
class TextureLibrary: public LibraryElement
{

public:

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	TextureLibrary();
	~TextureLibrary();

	unsigned int GetCount() const	{ return (unsigned int)vecElemTexture.size(); }

	void* GetElement(unsigned int index) const	{ _ASSERTE(index < GetCount()); return vecElemTexture[index]; }

private:

	VECTEXTUREELEM	vecElemTexture;
};


#endif	//___TextureLibrary_h___

#pragma once

#if !defined ___ImageLibrary_h___
#define ___ImageLibrary_h___

#include "LibraryElement.h"
#include "ImageElement.h"


// typeアトリビュートがIMAGEの<library>エレメントの情報を保存するクラス
class ImageLibrary: public LibraryElement
{

public:

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	ImageLibrary();
	~ImageLibrary();

	unsigned int GetCount() const	{ return (unsigned int)vecElemImage.size(); }
	
	void* GetElement(unsigned int index) const	{ _ASSERTE(index < GetCount()); return vecElemImage[index]; }

private:

	VECIMAGEELEM	vecElemImage;
};


#endif	//___ImageLibrary_h___
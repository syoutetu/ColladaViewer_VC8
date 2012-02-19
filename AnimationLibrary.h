
#pragma once

#if !defined ___AnimationLibrary_h___
#define ___AnimationLibrary_h___

#include "LibraryElement.h"
#include "AnimationElement.h"


// typeアトリビュートがANIMATIONの<library>エレメントの情報を保存するクラス
class AnimationLibrary: public LibraryElement
{

public:

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	AnimationLibrary();
	~AnimationLibrary();

	unsigned int GetCount() const	{ return (unsigned int)vecElemAnimation.size(); }

	void* GetElement(unsigned int index) const	{ _ASSERTE(index < GetCount()); return vecElemAnimation[index]; }

private:

	VECANIMATIONELEM	vecElemAnimation;
};


#endif	//___AnimationLibrary_h___
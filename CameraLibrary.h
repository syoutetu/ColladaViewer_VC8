
#pragma once

#if !defined ___CameraLibrary_h___
#define ___CameraLibrary_h___

#include "LibraryElement.h"
#include "CameraElement.h"


// typeアトリビュートがCAMERAの<library>エレメントの情報を保存するクラス
class CameraLibrary: public LibraryElement
{

public:

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	CameraLibrary();
	~CameraLibrary();

	unsigned int GetCount() const	{ return (unsigned int)vecElemCamera.size(); }
	
	void* GetElement(unsigned int index) const	{ _ASSERTE(index < GetCount()); return vecElemCamera[index]; }

private:

	VECCAMERAELEM	vecElemCamera;
};


#endif	//___CameraLibrary_h___
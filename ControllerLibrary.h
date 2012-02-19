
#pragma once

#if !defined ___ControllerLibrary_h___
#define ___ControllerLibrary_h___

#include "LibraryElement.h"
#include "ControllerElement.h"


// typeアトリビュートがCONTROLLERの<library>エレメントの情報を保存するクラス
class ControllerLibrary: public LibraryElement
{

public:

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	ControllerLibrary();
	~ControllerLibrary();

	unsigned int GetCount() const	{ return (unsigned int)vecElemController.size(); }
	
	void* GetElement(unsigned int index) const	{ _ASSERTE(index < GetCount()); return vecElemController[index]; }

private:

	VECCONTROLLERELEM	vecElemController;
};


#endif	//___ControllerLibrary_h___
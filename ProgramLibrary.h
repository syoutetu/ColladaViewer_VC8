
#pragma once

#if !defined ___ProgramLibrary_h___
#define ___ProgramLibrary_h___

#include "LibraryElement.h"
#include "ProgramElement.h"


// typeアトリビュートがPROGRAMの<library>エレメントの情報を保存するクラス
class ProgramLibrary: public LibraryElement
{

public:

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	ProgramLibrary();
	~ProgramLibrary();

	unsigned int GetCount() const	{ return (unsigned int)vecElemProgram.size(); }
		
	void* GetElement(unsigned int index) const	{ _ASSERTE(index < GetCount()); return vecElemProgram[index]; }

private:

	VECPROGRAMELEM	vecElemProgram;
};


#endif	//___ProgramLibrary_h___
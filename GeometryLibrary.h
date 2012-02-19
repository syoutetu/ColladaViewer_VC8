
#pragma once

#if !defined ___GeometryLibrary_h___
#define ___GeometryLibrary_h___

#include "LibraryElement.h"
#include "GeometryElement.h"


// type�A�g���r���[�g��GEOMETRY��<library>�G�������g�̏���ۑ�����N���X
class GeometryLibrary: public LibraryElement
{

public:

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
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
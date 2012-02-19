
#pragma once

#if !defined ___TrianglesElement_h___
#define ___TrianglesElement_h___


#include "BasePrimitive.h"


// <triangles>�G�������g�̏���ۑ�����N���X
class TrianglesElement: public BasePrimitive
{

public:

	TrianglesElement()	{}
	~TrianglesElement()	{}

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BasePrimitive::ValidElements( message, L"triangles" ); }

private:


};


typedef std::vector<TrianglesElement*>	VECTRIANGLESELEM;


#endif	//___TrianglesElement_h___
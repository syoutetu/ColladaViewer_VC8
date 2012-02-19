
#pragma once

#if !defined ___PolygonsElement_h___
#define ___PolygonsElement_h___


#include "BasePrimitive.h"


// <polygons>�G�������g�̏���ۑ�����N���X
class PolygonsElement: public BasePrimitive
{

public:

	PolygonsElement()	{}
	~PolygonsElement()	{}

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BasePrimitive::ValidElements( message, L"polygons" ); }

private:


};


typedef std::vector<PolygonsElement*>	VECPOLYGONSELEM;


#endif	//___PolygonsElement_h___
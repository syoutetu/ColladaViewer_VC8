
#pragma once

#if !defined ___LinestripsElement_h___
#define ___LinestripsElement_h___


#include "BasePrimitive.h"


// <linestrips>�G�������g�̏���ۑ�����N���X
class LinestripsElement: public BasePrimitive
{

public:

	LinestripsElement()		{}
	~LinestripsElement()	{}

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BasePrimitive::ValidElements( message, L"linestrips" ); }

private:


};


typedef std::vector<LinestripsElement*>	VECLINESTRIPSELEM;


#endif	//___LinestripsElement_h___
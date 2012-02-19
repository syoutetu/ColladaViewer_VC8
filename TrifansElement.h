
#pragma once

#if !defined ___TrifansElement_h___
#define ___TrifansElement_h___


#include "BasePrimitive.h"


// <trifans>�G�������g�̏���ۑ�����N���X
class TrifansElement: public BasePrimitive
{

public:

	TrifansElement()	{}
	~TrifansElement()	{}

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BasePrimitive::ValidElements( message, L"trifans" ); }

private:


};


typedef std::vector<TrifansElement*>	VECTRIFANSELEM;


#endif	//___TrifansElement_h___

#pragma once

#if !defined ___MatrixElement_h___
#define ___MatrixElement_h___


#include "BaseValue.h"


// <matrix>�G�������g�̏���ۑ�����N���X
class MatrixElement: public BaseValue
{

public:

	MatrixElement(): BaseValue( 16 )	{}	// 4x4float�K�v
	~MatrixElement()	{}

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	bool ValidElements(std::wstring& message) const	{ return BaseValue::ValidElements( message, L"matrix" ); }

private:


};


typedef std::vector<MatrixElement*>	VECMATRIXELEM;


#endif	//___MatrixElement_h___
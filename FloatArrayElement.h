
#pragma once

#if !defined ___FloatArrayElement_h___
#define ___FloatArrayElement_h___


#include "DomNodeReader.h"


// <float_array>�G�������g�̏���ۑ�����N���X
class FloatArrayElement: public DomNodeReader
{
public:

	static const int	DIGITS	= 6;		// digits�����̃f�t�H���g
	static const int	MAGNITUDE	= 38;	// magnitude�����̃f�t�H���g


	FloatArrayElement();
	~FloatArrayElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	unsigned int GetCount() const	{ return (unsigned int)valFloat.size(); }
	float GetValue(unsigned int index) const	{ _ASSERTE(index < GetCount()); return valFloat[index]; }

	unsigned int GetCountAttribute() const	{ return attrCount; }
	const std::wstring& GetIdAttribute() const	{ return attrId; }
	const std::wstring& GetNameAttribute() const	{ return attrName; }
	int GetDigitsAttribute() const	{ return attrDigits; }
	int GetMagnitudeAttribute() const	{ return attrMagnitude; }

private:

	//====================================
	// �A�g���r���[�g
	//====================================
	unsigned int	attrCount;		// Required
	std::wstring	attrId;			// �h�L�������g����Unique, Optional
	std::wstring	attrName;		// Optional
	int				attrDigits;		// Optional
	int				attrMagnitude;	// Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// �m�[�h�̒l
	//====================================
	std::vector<float>		valFloat;

	void ReadValue(const DOMNode* node);
};


typedef std::vector<FloatArrayElement*>	VECFLOATAELEM;


#endif	//___FloatArrayElement_h___

#pragma once

#if !defined ___ArrayElement_h___
#define ___ArrayElement_h___


#include "DomNodeReader.h"


// <array>�G�������g�̏���ۑ�����N���X
class ArrayElement: public DomNodeReader
{
public:

	static const int	MIN_INCLUSIVE	= -2147483647 - 1;	// minInclusive�����̃f�t�H���g
	static const int	MAX_INCLUSIVE	= 2147483647;		// maxInclusive�����̃f�t�H���g
	static const int	DIGITS	= 6;						// digits�����̃f�t�H���g
	static const int	MAGNITUDE	= 38;					// magnitude�����̃f�t�H���g



	ArrayElement();
	~ArrayElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// �A�g���r���[�g
	//====================================
	unsigned int		attrCount;			// Required
	std::wstring		attrId;				// �h�L�������g����Unique, Optional
	std::wstring		attrName;			// Optional
	std::wstring		attrType;			// Required
	int					attrMinInclusive;	// Optional
	int					attrMaxInclusive;	// Optional
	int					attrDigits;			// Optional
	int					attrMagnitude;		// Optional


	void ReadAttributes(const DOMNode* node);


	//====================================
	// �m�[�h�̒l(������)
	//====================================

};


typedef std::vector<ArrayElement*>	VECARRAYELEM;


#endif	//___ArrayElement_h___
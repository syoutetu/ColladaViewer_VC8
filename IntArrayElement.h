
#pragma once

#if !defined ___IntArrayElement_h___
#define ___IntArrayElement_h___


#include "DomNodeReader.h"


// <int_array>�G�������g�̏���ۑ�����N���X
class IntArrayElement: public DomNodeReader
{
public:

	static const int	MIN_INCLUSIVE	= -2147483647 - 1;	// minInclusive�����̃f�t�H���g
	static const int	MAX_INCLUSIVE	= 2147483647;		// maxInclusive�����̃f�t�H���g


	IntArrayElement();
	~IntArrayElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;

	
	unsigned int GetCount() const	{ return (unsigned int)valInt.size(); }
	int GetValue(unsigned int index) const	{ _ASSERTE(index < GetCount()); return valInt[index]; }

	unsigned int GetCountAttribute() const	{ return attrCount; }
	const std::wstring& GetIdAttribute() const	{ return attrId; }
	const std::wstring& GetNameAttribute() const	{ return attrName; }
	int GetMinInclusive() const	{ return attrMinInclusive; }
	int GetMaxInclusive() const	{ return attrMaxInclusive; }

private:

	//====================================
	// �A�g���r���[�g
	//====================================
	unsigned int	attrCount;			// Required
	std::wstring	attrId;				// �h�L�������g����Unique, Optional
	std::wstring	attrName;			// Optional
	int				attrMinInclusive;	// Optional
	int				attrMaxInclusive;	// Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// �m�[�h�̒l
	//====================================
	std::vector<int>		valInt;

	void ReadValue(const DOMNode* node);
};


typedef std::vector<IntArrayElement*>	VECINTAELEM;


#endif	//___IntArrayElement_h___
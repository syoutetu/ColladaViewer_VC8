
#pragma once

#if !defined ___BoolArrayElement_h___
#define ___BoolArrayElement_h___


#include "DomNodeReader.h"


// <bool_array>�G�������g�̏���ۑ�����N���X
class BoolArrayElement: public DomNodeReader
{
public:

	BoolArrayElement();
	~BoolArrayElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	unsigned int GetCount() const	{ return (unsigned int)valBool.size(); }
	bool GetValue(unsigned int index) const	{ _ASSERTE(index < GetCount()); return valBool[index]; }

	unsigned int GetCountAttribute() const	{ return attrCount; }
	const std::wstring& GetIdAttribute() const	{ return attrId; }
	const std::wstring& GetNameAttribute() const	{ return attrName; }

private:

	//====================================
	// �A�g���r���[�g
	//====================================
	unsigned int	attrCount;		// Required
	std::wstring	attrId;			// �h�L�������g����Unique, Optional
	std::wstring	attrName;		// Optional

	void ReadAttributes(const DOMNode* node);

	
	//====================================
	// �m�[�h�̒l
	//====================================
	std::vector<bool>		valBool;

	void ReadValue(const DOMNode* node);
};


typedef std::vector<BoolArrayElement*>	VECBOOLAELEM;


#endif	//___BoolArrayElement_h___

#pragma once

#if !defined ___NameArrayElement_h___
#define ___NameArrayElement_h___


#include "DomNodeReader.h"


// <Name_array>�G�������g�̏���ۑ�����N���X
class NameArrayElement: public DomNodeReader
{
public:

	NameArrayElement();
	~NameArrayElement();

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	unsigned int GetCount() const	{ return (unsigned int)valName.size(); }

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
	std::vector<std::wstring>	valName;

	void ReadValue(const DOMNode* node);
};


typedef std::vector<NameArrayElement*>	VECNAMEAELEM;


#endif	//___NameArrayElement_h___
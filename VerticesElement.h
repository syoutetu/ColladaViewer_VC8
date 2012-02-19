
#pragma once

#if !defined ___VerticesElement_h___
#define ___VerticesElement_h___


#include "DomNodeReader.h"

#include "InputElement.h"


// <vertices>�G�������g�̏���ۑ�����N���X
class VerticesElement: public DomNodeReader
{

public:

	VerticesElement();
	~VerticesElement();


	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	const std::wstring& GetIdAttribute() const	{ return attrId; }
	const std::wstring& GetNameAttribute() const	{ return attrName; }
	unsigned int GetCountAttribute() const	{ return attrCount; }

	unsigned int GetInputCount() const	{ return (unsigned int)vecElemInput.size(); }

	InputElement* GetInputElement(unsigned int index) const	{ _ASSERTE(index < GetInputCount()); return vecElemInput[index]; }
	InputElement* GetInputElementBySemantic(const std::wstring& semantic) const;
	InputElement* GetInputElementOfPositionSemantic() const	{ return GetInputElementBySemantic( L"POSITION" ); }
	InputElement* GetInputElementOfColorSemantic() const	{ return GetInputElementBySemantic( L"COLOR" ); }

private:

	//====================================
	// �A�g���r���[�g
	//====================================
	std::wstring		attrId;		// �h�L�������g����Unique, Optional
	std::wstring		attrName;	// Optional
	unsigned int		attrCount;	// Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// �G�������g
	//====================================
	VECINPUTELEM		vecElemInput;		// 1�ȏ㑶�݂���


};


typedef std::vector<VerticesElement*>	VECVERTICESELEM;


#endif	//___VerticesElement_h___
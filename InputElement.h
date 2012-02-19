
#pragma once

#if !defined ___InputElement_h___
#define ___InputElement_h___


#include "DomNodeReader.h"


// <input>�G�������g�̏���ۑ�����N���X
class InputElement: public DomNodeReader
{
public:

	InputElement();
	~InputElement();


	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	unsigned int GetIdxAttribute() const	{ return attrIdx; }
	const std::wstring& GetSemanticAttribute() const	{ return attrSemantic; }
	const std::wstring& GetSourceAttribute() const	{ return attrSource; }

	bool IsPositionSemantic() const	{ return attrSemantic.compare( L"POSITION" ) == 0; }
	bool IsNormalSemantic() const	{ return attrSemantic.compare( L"NORMAL" ) == 0; }
	bool IsTexCoordSemantic() const	{ return attrSemantic.compare( L"TEXCOORD" ) == 0; }

private:

	//====================================
	// �A�g���r���[�g
	//====================================
	unsigned int		attrIdx;		// �e�̗v�f��<combiner>�܂���<polygons>�Ȃǂ̏ꍇRequired
	std::wstring		attrSemantic;	// Required
	std::wstring		attrSource;		// Required

	void ReadAttributes(const DOMNode* node);
};


typedef std::vector<InputElement*>	VECINPUTELEM;


#endif	//___InputElement_h___
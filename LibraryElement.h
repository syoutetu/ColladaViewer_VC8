
#pragma once

#if !defined ___LibraryElement_h___
#define ___LibraryElement_h___


#include "DomNodeReader.h"


// <library>�G�������g�̏���ۑ����钊�ۃN���X
class LibraryElement: public DomNodeReader
{
public:

	enum TYPE {		// type�A�g���r���[�g�̎��
		TYPE_ANIMATION = 0,
		TYPE_CAMERA,
		TYPE_CODE,
		TYPE_CONTROLLER,
		TYPE_GEOMETRY,
		TYPE_IMAGE,
		TYPE_LIGHT,
		TYPE_MATERIAL,
		TYPE_PROGRAM,
		TYPE_TEXTURE,

		TYPE_Size	// ���̗񋓑̂̃T�C�Y
	};

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
//	virtual void ReadNode(const DOMNode* node)	{}
//	virtual bool ValidElements(std::wstring& message) const	{ return true; }

	virtual ~LibraryElement()	{}

	virtual unsigned int GetCount() const = 0;

	virtual void* GetElement(unsigned int index) const = 0;

	bool TypeOf(TYPE type) const	{ return this->type == type; }


protected:

	LibraryElement(TYPE t):type(t)	{}		// �C���X�^���X�͍쐬�ł��Ȃ�


	//====================================
	// �A�g���r���[�g
	//====================================
	std::wstring	id;		// �h�L�������g����Unique, Optional
	std::wstring	name;	// Optional
//	std::wstring	type;	// Required
	
	const TYPE	type;		// �R���X�g���N�^�Ŏ󂯎������͕s��

};


typedef std::vector<LibraryElement*>	VECLIBRARYELEM;


#endif	//___LibraryElement_h___
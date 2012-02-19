
#pragma once

#if !defined ___CameraLibrary_h___
#define ___CameraLibrary_h___

#include "LibraryElement.h"
#include "CameraElement.h"


// type�A�g���r���[�g��CAMERA��<library>�G�������g�̏���ۑ�����N���X
class CameraLibrary: public LibraryElement
{

public:

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	CameraLibrary();
	~CameraLibrary();

	unsigned int GetCount() const	{ return (unsigned int)vecElemCamera.size(); }
	
	void* GetElement(unsigned int index) const	{ _ASSERTE(index < GetCount()); return vecElemCamera[index]; }

private:

	VECCAMERAELEM	vecElemCamera;
};


#endif	//___CameraLibrary_h___
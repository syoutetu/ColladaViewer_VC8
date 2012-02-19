
#pragma once

#if !defined ___ControllerLibrary_h___
#define ___ControllerLibrary_h___

#include "LibraryElement.h"
#include "ControllerElement.h"


// type�A�g���r���[�g��CONTROLLER��<library>�G�������g�̏���ۑ�����N���X
class ControllerLibrary: public LibraryElement
{

public:

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	ControllerLibrary();
	~ControllerLibrary();

	unsigned int GetCount() const	{ return (unsigned int)vecElemController.size(); }
	
	void* GetElement(unsigned int index) const	{ _ASSERTE(index < GetCount()); return vecElemController[index]; }

private:

	VECCONTROLLERELEM	vecElemController;
};


#endif	//___ControllerLibrary_h___

#pragma once

#if !defined ___ColladaFile_h___
#define ___ColladaFile_h___


#include "ColladaObject.h"



class ColladaFile
{

public:

	ColladaFile();
	~ColladaFile();


	bool Load(LPCWSTR lpszFileName);					// Collada�t�@�C��(dae)��ǂݍ���
	//bool Save(LPCWSTR lpszFileName);					// Collada�t�@�C��(dae)��ۑ�����

	ColladaObject* GetColladaObject() const	{ return colladaObject; }


private:
	
	ColladaObject*	colladaObject;

	void CreateColladaObject(const DOMNode* rootNode);		// Collada�I�u�W�F�N�g���쐬����DOM�̃��[�g�m�[�h����f�[�^��ǂݍ���
};


#endif	//!defined ___ColladaFile_h___
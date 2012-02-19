
#pragma once

#if !defined ___ColladaFile_h___
#define ___ColladaFile_h___


#include "ColladaObject.h"



class ColladaFile
{

public:

	ColladaFile();
	~ColladaFile();


	bool Load(LPCWSTR lpszFileName);					// Colladaファイル(dae)を読み込む
	//bool Save(LPCWSTR lpszFileName);					// Colladaファイル(dae)を保存する

	ColladaObject* GetColladaObject() const	{ return colladaObject; }


private:
	
	ColladaObject*	colladaObject;

	void CreateColladaObject(const DOMNode* rootNode);		// Colladaオブジェクトを作成してDOMのルートノードからデータを読み込む
};


#endif	//!defined ___ColladaFile_h___
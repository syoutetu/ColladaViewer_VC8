
#pragma once

#if !defined ___LibraryElement_h___
#define ___LibraryElement_h___


#include "DomNodeReader.h"


// <library>エレメントの情報を保存する抽象クラス
class LibraryElement: public DomNodeReader
{
public:

	enum TYPE {		// typeアトリビュートの種類
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

		TYPE_Size	// この列挙体のサイズ
	};

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
//	virtual void ReadNode(const DOMNode* node)	{}
//	virtual bool ValidElements(std::wstring& message) const	{ return true; }

	virtual ~LibraryElement()	{}

	virtual unsigned int GetCount() const = 0;

	virtual void* GetElement(unsigned int index) const = 0;

	bool TypeOf(TYPE type) const	{ return this->type == type; }


protected:

	LibraryElement(TYPE t):type(t)	{}		// インスタンスは作成できない


	//====================================
	// アトリビュート
	//====================================
	std::wstring	id;		// ドキュメント内でUnique, Optional
	std::wstring	name;	// Optional
//	std::wstring	type;	// Required
	
	const TYPE	type;		// コンストラクタで受け取った後は不変

};


typedef std::vector<LibraryElement*>	VECLIBRARYELEM;


#endif	//___LibraryElement_h___
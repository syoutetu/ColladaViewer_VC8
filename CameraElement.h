
#pragma once

#if !defined ___CameraElement_h___
#define ___CameraElement_h___


#include "DomNodeReader.h"

#include "TechniqueElement.h"


// <camera>エレメントの情報を保存するクラス
class CameraElement: public DomNodeReader
{
public:

	CameraElement();
	~CameraElement();

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// アトリビュート
	//====================================
	std::wstring	attrId;		// ドキュメント内でUnique, Optional
	std::wstring	attrName;	// Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// エレメント
	//====================================
	VECTECHNIQUEELEM	vecElemTechnique;		// 1つ以上存在する
};


typedef std::vector<CameraElement*>	VECCAMERAELEM;


#endif	//___CameraElement_h___
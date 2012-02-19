
#pragma once

#if !defined ___SceneElement_h___
#define ___SceneElement_h___


#include "DomNodeReader.h"

#include "LookatElement.h"
#include "MatrixElement.h"
#include "PerspectiveElement.h"
#include "RotateElement.h"
#include "ScaleElement.h"
#include "SkewElement.h"
#include "TranslateElement.h"
#include "BoundingBoxElement.h"
#include "NodeElement.h"
#include "ExtraElement.h"


// <scene>エレメントの情報を保存するクラス
class SceneElement: public DomNodeReader
{
public:

	SceneElement();
	~SceneElement();


	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;

private:

	//====================================
	// アトリビュート
	//====================================
	std::wstring	attrId;		// Optional
	std::wstring	attrName;	// Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// エレメント
	//====================================
	VECLOOKATELEM		vecElemLookat;		// 0以上存在する
	VECMATRIXELEM		vecElemMatrix;		// 0以上存在する
	VECPERSPECTIVEELEM	vecElemPerspective;	// 0以上存在する
	VECROTATEELEM		vecElemRotate;		// 0以上存在する
	VECSCALEELEM		vecElemScale;		// 0以上存在する
	VECSKEWELEM			vecElemSkew;		// 0以上存在する
	VECTRANSLATEELEM	vecElemTranslate;	// 0以上存在する
	VECBOUNDINGBOXELEM	vecElemBoundingBox;	// 0以上存在する
	VECNODEELEM			vecElemNode;		// 0以上存在する
	VECEXTRAELEM		vecElemExtra;		// 0以上存在する
};


typedef std::vector<SceneElement*>	VECSCENEELEM;


#endif	//___SceneElement_h___
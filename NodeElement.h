
#pragma once

#if !defined ___NodeElement_h___
#define ___NodeElement_h___


#include "DomNodeReader.h"

#include "LookatElement.h"
#include "MatrixElement.h"
#include "PerspectiveElement.h"
#include "RotateElement.h"
#include "ScaleElement.h"
#include "SkewElement.h"
#include "TranslateElement.h"
#include "BoundingBoxElement.h"
#include "InstanceElement.h"
#include "ExtraElement.h"


class NodeElement;
typedef std::vector<NodeElement*>	VECNODEELEM;


// <node>エレメントの情報を保存するクラス
class NodeElement: public DomNodeReader
{

public:

	enum TYPE {
		TYPE_JOINT,
		TYPE_NODE,

		TYPE_Size
	};


	NodeElement();
	~NodeElement();

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
	TYPE			attrType;	// Optional

	void ReadAttributes(const DOMNode* node);

	void SetType(const XMLCh* type);


	//====================================
	// エレメント
	//====================================
	VECLOOKATELEM		vecElemLookat;			// 0以上存在する
	VECMATRIXELEM		vecElemMatrix;			// 0以上存在する
	VECPERSPECTIVEELEM	vecElemPerspective;		// 0以上存在する
	VECROTATEELEM		vecElemRotate;			// 0以上存在する
	VECSCALEELEM		vecElemScale;			// 0以上存在する
	VECSKEWELEM			vecElemSkew;			// 0以上存在する
	VECTRANSLATEELEM	vecElemTranslate;		// 0以上存在する
	VECBOUNDINGBOXELEM	vecElemBoundingBox;		// 0以上存在する
	VECINSTANCEELEM		vecElemInstance;		// 0以上存在する
	VECNODEELEM			vecElemNode;			// 0以上存在する
	VECEXTRAELEM		vecElemExtra;			// 0以上存在する

};


#endif	//___NodeElement_h___
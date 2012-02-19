
#pragma once

#if !defined ___JointsElement_h___
#define ___JointsElement_h___


#include "DomNodeReader.h"

#include "InputElement.h"


// <joints>エレメントの情報を保存するクラス
class JointsElement: public DomNodeReader
{

public:

	JointsElement();
	~JointsElement();

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
	unsigned int	attrCount;	// Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// エレメント
	//====================================
	VECINPUTELEM		vecElemInput;		// 2つ以上存在する

};


typedef std::vector<JointsElement*>	VECJOINTSELEM;


#endif	//___JointsElement_h___
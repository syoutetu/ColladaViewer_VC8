
#pragma once

#if !defined ___ImageElement_h___
#define ___ImageElement_h___


#include "DomNodeReader.h"


// <image>エレメントの情報を保存するクラス
class ImageElement: public DomNodeReader
{
public:

	ImageElement();
	~ImageElement();


	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


private:

	//====================================
	// アトリビュート
	//====================================
	std::wstring		attrId;			// ドキュメント内でUnique, Optional
	std::wstring		attrName;		// Optional
	std::wstring		attrSource;		// Optional
	std::wstring		attrFormat;		// Optional
	unsigned int		attrHeight;		// Optional
	unsigned int		attrWidth;		// Optional
	unsigned int		attrDepth;		// Optional

	void ReadAttributes(const DOMNode* node);
};


typedef std::vector<ImageElement*>	VECIMAGEELEM;


#endif	//___ImageElement_h___
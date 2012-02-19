
#pragma once

#if !defined ___FloatArrayElement_h___
#define ___FloatArrayElement_h___


#include "DomNodeReader.h"


// <float_array>エレメントの情報を保存するクラス
class FloatArrayElement: public DomNodeReader
{
public:

	static const int	DIGITS	= 6;		// digits属性のデフォルト
	static const int	MAGNITUDE	= 38;	// magnitude属性のデフォルト


	FloatArrayElement();
	~FloatArrayElement();

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;


	unsigned int GetCount() const	{ return (unsigned int)valFloat.size(); }
	float GetValue(unsigned int index) const	{ _ASSERTE(index < GetCount()); return valFloat[index]; }

	unsigned int GetCountAttribute() const	{ return attrCount; }
	const std::wstring& GetIdAttribute() const	{ return attrId; }
	const std::wstring& GetNameAttribute() const	{ return attrName; }
	int GetDigitsAttribute() const	{ return attrDigits; }
	int GetMagnitudeAttribute() const	{ return attrMagnitude; }

private:

	//====================================
	// アトリビュート
	//====================================
	unsigned int	attrCount;		// Required
	std::wstring	attrId;			// ドキュメント内でUnique, Optional
	std::wstring	attrName;		// Optional
	int				attrDigits;		// Optional
	int				attrMagnitude;	// Optional

	void ReadAttributes(const DOMNode* node);


	//====================================
	// ノードの値
	//====================================
	std::vector<float>		valFloat;

	void ReadValue(const DOMNode* node);
};


typedef std::vector<FloatArrayElement*>	VECFLOATAELEM;


#endif	//___FloatArrayElement_h___
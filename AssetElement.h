
#pragma once

#if !defined ___AssetElement_h___
#define ___AssetElement_h___


#include "DomNodeReader.h"


// <asset>エレメントの情報を保存するクラス
class AssetElement: public DomNodeReader
{
public:

	enum AXIS {		// up_axisエレメントの値
		AXIS_X,
		AXIS_Y,
		AXIS_Z,

		AXIS_Size
	};


	AssetElement();
	~AssetElement()	{}

	//============================================
	// DomNodeReader インターフェースの実装
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;



	// <unit>要素のmeter属性に設定された単位を取得する
	float GetUnitMeterAttribute() const	{ return attrUnitMeter; }

	// <up_axis>要素に設定された上向きの軸を取得する
	AXIS GetUpAxis() const	{ return elemUpAxis; }

private:

	float	attrUnitMeter;			// <unit meter>の値
	AXIS	elemUpAxis;				// <up_axis>の値

	//========================================================
	// エレメント(<asset>でしか使われない要素をここで管理する)
	//========================================================
	std::wstring	elemAuthor;				// <author>				// 0以上存在	
	std::wstring	elemAuthoringTool;		// <authoring_tool>		// 0または1つ存在
	std::wstring	elemCreated;			// <created>			// 0または1つ存在
	std::wstring	elemModified;			// <modified>			// 0または1つ存在
	std::wstring	elemRevision;			// <revision>			// 0または1つ存在
	std::wstring	elemSourceData;			// <source_data>		// 0または1つ存在
	std::wstring	elemCopyright;			// <copyright>			// 0以上存在	
	std::wstring	elemTitle;				// <title>				// 0または1つ存在
	std::wstring	elemSubject;			// <subject>			// 0または1つ存在
	std::wstring	elemKeywords;			// <keywords>			// 0以上存在	
	std::wstring	elemComments;			// <comments>			// 0以上存在	
	std::wstring	elemUnitName;			// <unit name>			// 0または1つ存在
	std::wstring	elemUnitMeter;			// <unit meter>			// 0または1つ存在
//	std::wstring	elemUpAxis;				// <up_axis>			// 0または1つ存在


	void SetUpAxis(const XMLCh* up);
	void ReadUnitAttributes(const DOMNode* nodeUnit);

};


#endif	//___AssetElement_h___
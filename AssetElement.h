
#pragma once

#if !defined ___AssetElement_h___
#define ___AssetElement_h___


#include "DomNodeReader.h"


// <asset>�G�������g�̏���ۑ�����N���X
class AssetElement: public DomNodeReader
{
public:

	enum AXIS {		// up_axis�G�������g�̒l
		AXIS_X,
		AXIS_Y,
		AXIS_Z,

		AXIS_Size
	};


	AssetElement();
	~AssetElement()	{}

	//============================================
	// DomNodeReader �C���^�[�t�F�[�X�̎���
	//============================================
	void ReadNode(const DOMNode* node);
	bool ValidElements(std::wstring& message) const;



	// <unit>�v�f��meter�����ɐݒ肳�ꂽ�P�ʂ��擾����
	float GetUnitMeterAttribute() const	{ return attrUnitMeter; }

	// <up_axis>�v�f�ɐݒ肳�ꂽ������̎����擾����
	AXIS GetUpAxis() const	{ return elemUpAxis; }

private:

	float	attrUnitMeter;			// <unit meter>�̒l
	AXIS	elemUpAxis;				// <up_axis>�̒l

	//========================================================
	// �G�������g(<asset>�ł����g���Ȃ��v�f�������ŊǗ�����)
	//========================================================
	std::wstring	elemAuthor;				// <author>				// 0�ȏ㑶��	
	std::wstring	elemAuthoringTool;		// <authoring_tool>		// 0�܂���1����
	std::wstring	elemCreated;			// <created>			// 0�܂���1����
	std::wstring	elemModified;			// <modified>			// 0�܂���1����
	std::wstring	elemRevision;			// <revision>			// 0�܂���1����
	std::wstring	elemSourceData;			// <source_data>		// 0�܂���1����
	std::wstring	elemCopyright;			// <copyright>			// 0�ȏ㑶��	
	std::wstring	elemTitle;				// <title>				// 0�܂���1����
	std::wstring	elemSubject;			// <subject>			// 0�܂���1����
	std::wstring	elemKeywords;			// <keywords>			// 0�ȏ㑶��	
	std::wstring	elemComments;			// <comments>			// 0�ȏ㑶��	
	std::wstring	elemUnitName;			// <unit name>			// 0�܂���1����
	std::wstring	elemUnitMeter;			// <unit meter>			// 0�܂���1����
//	std::wstring	elemUpAxis;				// <up_axis>			// 0�܂���1����


	void SetUpAxis(const XMLCh* up);
	void ReadUnitAttributes(const DOMNode* nodeUnit);

};


#endif	//___AssetElement_h___
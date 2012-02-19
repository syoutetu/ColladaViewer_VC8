// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// Windows �w�b�_�[����g�p����Ă��Ȃ����������O����
#define VC_EXTRALEAN			// �g�p�p�x�̒Ⴂ API �����O����
#define STRICT					// �^�������Ɉ���

// Windows �w�b�_�[ �t�@�C��:
#include <windows.h>
#include <shlwapi.h>
// C �����^�C�� �w�b�_�[ �t�@�C��:
//#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>
//#include <tchar.h>		// TCHAR�͎g��Ȃ�(���ׂă��C�h��������g�p����)
#include <crtdbg.h>

// STL:
#include <string>
#include <vector>

// �o�b�t�@�ɑ΂��Ĉ��S�łȂ������񑀍�������(StringCxx�֐����g��)
#include <strsafe.h>

// DirectX9:
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr9.h>

// xerces XML�p�[�T�[:
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/TransService.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMWriter.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

XERCES_CPP_NAMESPACE_USE		// XERCES_CPP_NAMESPACE���O��Ԃ��g�p����


// ====================================
// �}�N��
// ====================================
#define SAFE_DELETE(p)			{ delete (p); (p) = NULL; }
#define SAFE_DELETE_ARRAY(p)	{ delete[] (p); (p) = NULL; }
#define SAFE_RELEASE(p)			{ if((p) != NULL) { (p)->Release(); (p) = NULL; } }

#define L_STR2(x)			L##x		// 2�i�K�ŕ������W�J�����(���ڎg�p���Ă͂����Ȃ�)
#define L_STR(x)			L_STR2(x)	// �}�N����`����Ă��镶�����L��t����


// D3DVERTEXELEMENT9�\���̂̃f�[�^(ID3DXMesh�I�u�W�F�N�g���쐬����Ƃ��Ɏg�p����):
#define DECL_VERTEXELEM_POSITION(p)	{ 0, p, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 }
#define DECL_VERTEXELEM_NORMAL(p)	{ 0, p, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 }
#define DECL_VERTEXELEM_TEXCOORD(p)	{ 0, p, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 }


// ====================================
// �O���[�o���֐�
// ====================================
// �v�f�m�[�h�̏ꍇ��true��Ԃ�
inline bool IsElementNode(const DOMNode* node)
{
	_ASSERTE(node !=NULL);

	return node->getNodeType() == DOMNode::ELEMENT_NODE;
}

// ��������𐮐��ɕϊ�����
inline int XMLChToInt(const XMLCh* value)
{
	_ASSERTE(value != NULL);
	_ASSERTE(sizeof(XMLCh) == sizeof(wchar_t));
	
	wchar_t* stop = NULL;
	long l = wcstol( (const wchar_t*)value, &stop, 10 );

	_ASSERTE(stop == (const wchar_t*)value + wcslen( (const wchar_t*)value ));

	return (int)l;
}

// ������𕄍����������ɕϊ�����
inline unsigned int XMLChToUInt(const XMLCh* value)
{
	_ASSERTE(value != NULL);
	_ASSERTE(sizeof(XMLCh) == sizeof(wchar_t));

	wchar_t* stop = NULL;
	unsigned long ul = wcstoul( (const wchar_t*)value, &stop, 10 );

	_ASSERTE(stop == (const wchar_t*)value + wcslen( (const wchar_t*)value ));

	return (unsigned int)ul;
}

// ������𕂓������ɕϊ�����
inline double XMLChToDouble(const XMLCh* value)
{
	_ASSERTE(value != NULL);
	_ASSERTE(sizeof(XMLCh) == sizeof(wchar_t));
	
	wchar_t* stop = NULL;
	double d = wcstod( (const wchar_t*)value, &stop );

	_ASSERTE(stop == (const wchar_t*)value + wcslen( (const wchar_t*)value ));

	return d;
}

inline float XMLChToFloat(const XMLCh* value)
{
	return (float)XMLChToDouble( value );
}

// ������"TRUE"(�啶���Ə������̋�ʖ���)�̏ꍇ��ture��Ԃ�
inline bool XMLChToBool(const XMLCh* value)
{
	_ASSERTE(value != NULL);
	_ASSERTE(sizeof(XMLCh) == sizeof(wchar_t));

	return _wcsicmp( (const wchar_t*)value, L"true" ) == 0;
}

// node�̒l��value���������ꍇ��true��Ԃ�
inline bool IsNodeValueEquals(const DOMNode* node, const wchar_t* value)
{ 
	_ASSERTE(node != NULL);
	_ASSERTE(value != NULL);
	_ASSERTE(sizeof(XMLCh) == sizeof(wchar_t));

	return wcscmp( (const wchar_t*)node->getNodeValue(), value ) == 0;
}

// node�̍ŏ��̎q�m�[�h�̒l��str�Ɏ擾����
inline void GetFirstChildNodeValue(const DOMNode* node, std::wstring& str)
{
	_ASSERTE(node != NULL);
	_ASSERTE(str.empty());
	_ASSERTE(sizeof(XMLCh) == sizeof(wchar_t));

	if( node->hasChildNodes() ) { str = (const wchar_t*)node->getFirstChild()->getNodeValue(); }
}

// ��̕�����ł͂Ȃ�value��wstring�ϐ��ɑ������
inline void SetStringValue(std::wstring& store, const XMLCh* value)
{
	_ASSERTE(value != NULL);
	_ASSERTE(sizeof(XMLCh) == sizeof(wchar_t));

	if( value[0] == L'\0' ) { return; }		// ��̕�����̏ꍇ�͐ݒ肵�Ȃ�
	store = (const wchar_t*)value;
}

// ��̕�����ł͂Ȃ�value��int�ϐ��ɑ������
inline void SetIntValue(int& store, const XMLCh* value)
{
	_ASSERTE(value != NULL);
	if( value[0] == L'\0' ) { return; }		// ��̕�����̏ꍇ�͐ݒ肵�Ȃ�
	store = XMLChToInt( value );
}

// ��̕�����ł͂Ȃ�value��unsignedint�ϐ��ɑ������
inline void SetUIntValue(unsigned int& store, const XMLCh* value)
{
	_ASSERTE(value != NULL);
	if( value[0] == L'\0' ) { return; }		// ��̕�����̏ꍇ�͐ݒ肵�Ȃ�
	store = XMLChToUInt( value );
}

// ��̕�����ł͂Ȃ�value��double�ϐ��ɑ������
inline void SetDoubleValue(double& store, const XMLCh* value)
{
	_ASSERTE(value != NULL);
	if( value[0] == L'\0' ) { return; }		// ��̕�����̏ꍇ�͐ݒ肵�Ȃ�
	store = XMLChToDouble( value );
}

// ��̕�����ł͂Ȃ�value��float�ϐ��ɑ������
inline void SetFloatValue(float& store, const XMLCh* value)
{
	_ASSERTE(value != NULL);
	if( value[0] == L'\0' ) { return; }		// ��̕�����̏ꍇ�͐ݒ肵�Ȃ�
	store = XMLChToFloat( value );
}

// ��̕�����ł͂Ȃ�value��bool�ϐ��ɑ������
inline void SetBoolValue(bool& store, const XMLCh* value)
{
	_ASSERTE(value != NULL);
	if( value[0] == L'\0' ) { return; }		// ��̕�����̏ꍇ�͐ݒ肵�Ȃ�
	store = XMLChToBool( value );
}


// �ŏ��̕�����'#'�̏ꍇ�͎�菜��
inline void TrimFirstSharpChar(std::wstring& str)
{
	if( str.empty() ) { return; }
	if( str[0] == L'#' ) { str.erase( str.begin() ); }
}


// �s�̐擪�Ƀ^�v��}������
inline void InsertTabEachLine(std::wstring& str)
{
	std::wstring::size_type offset = 0;

	do
	{
		str.insert( offset, 1, L'\t' );
		offset = str.find( L'\n', offset + 1 );
	} while( offset++ != std::wstring::npos );
}



// ====================================
// �e���v���[�g�֐�
// ====================================
template<typename _Tn>		// _Tn�|�C���^�̃x�N�^�[�̒��g��������ăx�N�^�[��clear����
inline void ClearVector(std::vector<_Tn*>& vec)
{
	typename std::vector<_Tn*>::iterator it, itEnd = vec.end();
	for( it = vec.begin(); it != itEnd; ++it )	{ SAFE_DELETE(*it); }
	vec.clear();
}



#include "ColladaElementName.h"		// COLLADA�v�f�̖��O�𔻒肷��֐�
#include "ColladaAttributeName.h"	// COLLADA�������擾����֐�



// xerces����new���I�[�o�[���[�h���Ă���̂ŃR�����g�A�E�g
//#define _CRTDBG_MAP_ALLOC	// <crtdbg.h>�Ń��������[�N����������
//#include <crtdbg.h>
//
//// new�̃��������[�N���������邽�߂ɒu��������
//#ifdef _DEBUG
//
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//
//#endif



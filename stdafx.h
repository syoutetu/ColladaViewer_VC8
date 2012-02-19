// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// Windows ヘッダーから使用されていない部分を除外する
#define VC_EXTRALEAN			// 使用頻度の低い API を除外する
#define STRICT					// 型を厳密に扱う

// Windows ヘッダー ファイル:
#include <windows.h>
#include <shlwapi.h>
// C ランタイム ヘッダー ファイル:
//#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>
//#include <tchar.h>		// TCHARは使わない(すべてワイド文字列を使用する)
#include <crtdbg.h>

// STL:
#include <string>
#include <vector>

// バッファに対して安全でない文字列操作を避ける(StringCxx関数を使う)
#include <strsafe.h>

// DirectX9:
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr9.h>

// xerces XMLパーサー:
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

XERCES_CPP_NAMESPACE_USE		// XERCES_CPP_NAMESPACE名前空間を使用する


// ====================================
// マクロ
// ====================================
#define SAFE_DELETE(p)			{ delete (p); (p) = NULL; }
#define SAFE_DELETE_ARRAY(p)	{ delete[] (p); (p) = NULL; }
#define SAFE_RELEASE(p)			{ if((p) != NULL) { (p)->Release(); (p) = NULL; } }

#define L_STR2(x)			L##x		// 2段階で文字列を展開する為(直接使用してはいけない)
#define L_STR(x)			L_STR2(x)	// マクロ定義されている文字列にLを付ける


// D3DVERTEXELEMENT9構造体のデータ(ID3DXMeshオブジェクトを作成するときに使用する):
#define DECL_VERTEXELEM_POSITION(p)	{ 0, p, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 }
#define DECL_VERTEXELEM_NORMAL(p)	{ 0, p, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 }
#define DECL_VERTEXELEM_TEXCOORD(p)	{ 0, p, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 }


// ====================================
// グローバル関数
// ====================================
// 要素ノードの場合はtrueを返す
inline bool IsElementNode(const DOMNode* node)
{
	_ASSERTE(node !=NULL);

	return node->getNodeType() == DOMNode::ELEMENT_NODE;
}

// 文字列をを整数に変換する
inline int XMLChToInt(const XMLCh* value)
{
	_ASSERTE(value != NULL);
	_ASSERTE(sizeof(XMLCh) == sizeof(wchar_t));
	
	wchar_t* stop = NULL;
	long l = wcstol( (const wchar_t*)value, &stop, 10 );

	_ASSERTE(stop == (const wchar_t*)value + wcslen( (const wchar_t*)value ));

	return (int)l;
}

// 文字列を符号無し整数に変換する
inline unsigned int XMLChToUInt(const XMLCh* value)
{
	_ASSERTE(value != NULL);
	_ASSERTE(sizeof(XMLCh) == sizeof(wchar_t));

	wchar_t* stop = NULL;
	unsigned long ul = wcstoul( (const wchar_t*)value, &stop, 10 );

	_ASSERTE(stop == (const wchar_t*)value + wcslen( (const wchar_t*)value ));

	return (unsigned int)ul;
}

// 文字列を浮動小数に変換する
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

// 文字列が"TRUE"(大文字と小文字の区別無し)の場合はtureを返す
inline bool XMLChToBool(const XMLCh* value)
{
	_ASSERTE(value != NULL);
	_ASSERTE(sizeof(XMLCh) == sizeof(wchar_t));

	return _wcsicmp( (const wchar_t*)value, L"true" ) == 0;
}

// nodeの値とvalueが等しい場合はtrueを返す
inline bool IsNodeValueEquals(const DOMNode* node, const wchar_t* value)
{ 
	_ASSERTE(node != NULL);
	_ASSERTE(value != NULL);
	_ASSERTE(sizeof(XMLCh) == sizeof(wchar_t));

	return wcscmp( (const wchar_t*)node->getNodeValue(), value ) == 0;
}

// nodeの最初の子ノードの値をstrに取得する
inline void GetFirstChildNodeValue(const DOMNode* node, std::wstring& str)
{
	_ASSERTE(node != NULL);
	_ASSERTE(str.empty());
	_ASSERTE(sizeof(XMLCh) == sizeof(wchar_t));

	if( node->hasChildNodes() ) { str = (const wchar_t*)node->getFirstChild()->getNodeValue(); }
}

// 空の文字列ではないvalueをwstring変数に代入する
inline void SetStringValue(std::wstring& store, const XMLCh* value)
{
	_ASSERTE(value != NULL);
	_ASSERTE(sizeof(XMLCh) == sizeof(wchar_t));

	if( value[0] == L'\0' ) { return; }		// 空の文字列の場合は設定しない
	store = (const wchar_t*)value;
}

// 空の文字列ではないvalueをint変数に代入する
inline void SetIntValue(int& store, const XMLCh* value)
{
	_ASSERTE(value != NULL);
	if( value[0] == L'\0' ) { return; }		// 空の文字列の場合は設定しない
	store = XMLChToInt( value );
}

// 空の文字列ではないvalueをunsignedint変数に代入する
inline void SetUIntValue(unsigned int& store, const XMLCh* value)
{
	_ASSERTE(value != NULL);
	if( value[0] == L'\0' ) { return; }		// 空の文字列の場合は設定しない
	store = XMLChToUInt( value );
}

// 空の文字列ではないvalueをdouble変数に代入する
inline void SetDoubleValue(double& store, const XMLCh* value)
{
	_ASSERTE(value != NULL);
	if( value[0] == L'\0' ) { return; }		// 空の文字列の場合は設定しない
	store = XMLChToDouble( value );
}

// 空の文字列ではないvalueをfloat変数に代入する
inline void SetFloatValue(float& store, const XMLCh* value)
{
	_ASSERTE(value != NULL);
	if( value[0] == L'\0' ) { return; }		// 空の文字列の場合は設定しない
	store = XMLChToFloat( value );
}

// 空の文字列ではないvalueをbool変数に代入する
inline void SetBoolValue(bool& store, const XMLCh* value)
{
	_ASSERTE(value != NULL);
	if( value[0] == L'\0' ) { return; }		// 空の文字列の場合は設定しない
	store = XMLChToBool( value );
}


// 最初の文字が'#'の場合は取り除く
inline void TrimFirstSharpChar(std::wstring& str)
{
	if( str.empty() ) { return; }
	if( str[0] == L'#' ) { str.erase( str.begin() ); }
}


// 行の先頭にタプを挿入する
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
// テンプレート関数
// ====================================
template<typename _Tn>		// _Tnポインタのベクターの中身を解放してベクターをclearする
inline void ClearVector(std::vector<_Tn*>& vec)
{
	typename std::vector<_Tn*>::iterator it, itEnd = vec.end();
	for( it = vec.begin(); it != itEnd; ++it )	{ SAFE_DELETE(*it); }
	vec.clear();
}



#include "ColladaElementName.h"		// COLLADA要素の名前を判定する関数
#include "ColladaAttributeName.h"	// COLLADA属性を取得する関数



// xerces側でnewをオーバーロードしているのでコメントアウト
//#define _CRTDBG_MAP_ALLOC	// <crtdbg.h>でメモリリークを検査する
//#include <crtdbg.h>
//
//// newのメモリリークを検査するために置き換える
//#ifdef _DEBUG
//
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//
//#endif



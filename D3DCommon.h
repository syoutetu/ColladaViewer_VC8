
#pragma once

#if !defined ___D3DCommon_h___
#define ___D3DCommon_h___



void ShowErrorMessage(HRESULT hr, LPCWSTR lpszFile, const DWORD dwLine, LPCWSTR lpszTrace);	// Direct3Dのエラーメッセージを表示する


#ifdef _DEBUG
	#define VALID(x)           { hr = x; if( FAILED(hr) ) { ShowErrorMessage( hr, L_STR(__FILE__), (DWORD)__LINE__, L#x ); } }
	#define VALID_RETURN(x)    { hr = x; if( FAILED(hr) ) { ShowErrorMessage( hr, L_STR(__FILE__), (DWORD)__LINE__, L#x ); return false; } }
#else
	#define VALID(x)           { hr = x; }
	#define VALID_RETURN(x)    { hr = x; if( FAILED(hr) ) { return false; } }
#endif


#endif	//___D3DCommon_h___
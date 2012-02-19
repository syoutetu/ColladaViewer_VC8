#include "stdafx.h"





void ShowErrorMessage(const HRESULT hr, LPCWSTR lpszFile, const DWORD dwLine, LPCWSTR lpszTrace)
{
	if( SUCCEEDED(hr) ) { return; }

	std::wstring strMessage = L"Direct3D でエラーが発生しました\n\n";

	WCHAR szTemp[512];
	StringCchPrintf( szTemp, 512, L"ファイル[%s] - Line[%u]\n%s\n\n", lpszFile, dwLine, lpszTrace );
	szTemp[512 - 1] = L'\0';
	strMessage += szTemp;

	switch( hr )
	{
	case D3DERR_INVALIDCALL:
		strMessage += L"D3DERR_INVALIDCALL: メソッドの呼び出しが無効です。たとえば、メソッドのパラメータに無効な値が設定されている場合などです。";
		break;
	case D3DXERR_INVALIDDATA:
		strMessage += L"D3DXERR_INVALIDDATA: データが無効です。";
		break;
	case D3DERR_NOTAVAILABLE:
		strMessage += L"D3DERR_NOTAVAILABLE: このデバイスは、問い合わせたテクニックをサポートしていません。";
		break;
	case D3DERR_OUTOFVIDEOMEMORY:
		strMessage += L"D3DERR_OUTOFVIDEOMEMORY: Direct3D が処理を行うのに十分なディスプレイメモリがありません。";
		break;
	case D3DERR_DEVICELOST:
		strMessage += L"D3DERR_DEVICELOST: デバイスは、消失していますが、現在リセットできません。したがって、レンダリングは不可能です。"; 
		break;
	case D3DERR_DRIVERINTERNALERROR:
		strMessage += L"D3DERR_DRIVERINTERNALERROR: 内部ドライバエラーです。アプリケーションはシャットダウンしなければなりません。";
		break;
	case E_OUTOFMEMORY:
		strMessage += L"E_OUTOFMEMORY: Direct3D が呼び出しを完了するための十分なメモリを割り当てることができませんでした。";
		break;
	}

	MessageBox( NULL, strMessage.c_str(), L"Direct3Dエラー", MB_OK | MB_ICONERROR );
}

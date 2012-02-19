#include "stdafx.h"





void ShowErrorMessage(const HRESULT hr, LPCWSTR lpszFile, const DWORD dwLine, LPCWSTR lpszTrace)
{
	if( SUCCEEDED(hr) ) { return; }

	std::wstring strMessage = L"Direct3D �ŃG���[���������܂���\n\n";

	WCHAR szTemp[512];
	StringCchPrintf( szTemp, 512, L"�t�@�C��[%s] - Line[%u]\n%s\n\n", lpszFile, dwLine, lpszTrace );
	szTemp[512 - 1] = L'\0';
	strMessage += szTemp;

	switch( hr )
	{
	case D3DERR_INVALIDCALL:
		strMessage += L"D3DERR_INVALIDCALL: ���\�b�h�̌Ăяo���������ł��B���Ƃ��΁A���\�b�h�̃p�����[�^�ɖ����Ȓl���ݒ肳��Ă���ꍇ�Ȃǂł��B";
		break;
	case D3DXERR_INVALIDDATA:
		strMessage += L"D3DXERR_INVALIDDATA: �f�[�^�������ł��B";
		break;
	case D3DERR_NOTAVAILABLE:
		strMessage += L"D3DERR_NOTAVAILABLE: ���̃f�o�C�X�́A�₢���킹���e�N�j�b�N���T�|�[�g���Ă��܂���B";
		break;
	case D3DERR_OUTOFVIDEOMEMORY:
		strMessage += L"D3DERR_OUTOFVIDEOMEMORY: Direct3D ���������s���̂ɏ\���ȃf�B�X�v���C������������܂���B";
		break;
	case D3DERR_DEVICELOST:
		strMessage += L"D3DERR_DEVICELOST: �f�o�C�X�́A�������Ă��܂����A���݃��Z�b�g�ł��܂���B���������āA�����_�����O�͕s�\�ł��B"; 
		break;
	case D3DERR_DRIVERINTERNALERROR:
		strMessage += L"D3DERR_DRIVERINTERNALERROR: �����h���C�o�G���[�ł��B�A�v���P�[�V�����̓V���b�g�_�E�����Ȃ���΂Ȃ�܂���B";
		break;
	case E_OUTOFMEMORY:
		strMessage += L"E_OUTOFMEMORY: Direct3D ���Ăяo�����������邽�߂̏\���ȃ����������蓖�Ă邱�Ƃ��ł��܂���ł����B";
		break;
	}

	MessageBox( NULL, strMessage.c_str(), L"Direct3D�G���[", MB_OK | MB_ICONERROR );
}

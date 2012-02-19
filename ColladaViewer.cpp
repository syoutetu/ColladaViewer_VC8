// ColladaViewer.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"

#include "D3DObject.h"
#include "ColladaFile.h"
#include "ColladaViewer.h"


#define MAX_LOADSTRING 100


#define MIN_WINDOW_SIZE_X	320	// �E�B���h�E�̕��̍ŏ��l
#define MIN_WINDOW_SIZE_Y	240	// �E�B���h�E�̍����̍ŏ��l
#define DEF_WINDOW_SIZE_X	640	// �E�B���h�E�̕��̕W���l
#define DEF_WINDOW_SIZE_Y	480	// �E�B���h�E�̍����̕W���l

#define DEF_COLLADA_FILE_NAME	L"collada.dae"	// �W���œǂݍ���COLLADA�t�@�C��

// �O���[�o���ϐ� :
HINSTANCE hInst;								// ���݂̃C���^�[�t�F�C�X
WCHAR szTitle[MAX_LOADSTRING];					// �^�C�g�� �o�[�̃e�L�X�g
WCHAR szWindowClass[MAX_LOADSTRING];			// ���C�� �E�B���h�E �N���X��


// ���̃R�[�h ���W���[���Ɋ܂܂��֐��̐錾��]�����܂� :
ATOM				MyRegisterClass(HINSTANCE hInstance);
HWND				InitInstance(HINSTANCE);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
// xerces����new���I�[�o�[���[�h���Ă���̂ŃR�����g�A�E�g
//#if _DEBUG
//	// ���������[�N������������@��ݒ肷��:
//	int iFlag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );
//
//	iFlag |= _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_EVERY_128_DF;
//
//	_CrtSetDbgFlag( iFlag );
//#endif


	// �O���[�o������������������Ă��܂��B
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_COLLADAVIEWER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// �A�v���P�[�V�����̏����������s���܂��B:
	HWND hWnd = InitInstance( hInstance );
	if( hWnd == NULL )
	{
		MessageBox( NULL, L"�E�B���h�E�̍쐬�Ɏ��s���܂���", L"�E�B���h�E�̍쐬", MB_OK | MB_ICONERROR );
		return 1;
	}

	// Direct3D�̃I�u�W�F�N�g���쐬���ď���������:
	CD3DObject& d3dObject = GetD3DObject();
	if( d3dObject.Initialize( hWnd ) == false )
	{
		MessageBox( NULL, L"Direct3D�I�u�W�F�N�g�̏������Ɏ��s���܂���", L"Direct3D�̏�����", MB_OK | MB_ICONERROR );
		return 1;
	}


	try
	{
		xercesc::XMLPlatformUtils::Initialize();	// �N���C�A���g�R�[�h�̍ŏ��ɕK�v
	}
	catch( const xercesc::XMLException& ex )
	{
		std::wstring strMessage = L"XML�p�[�T�[�̏������ŃG���[���������܂���\n\n";
		strMessage += (wchar_t*)ex.getMessage();
		MessageBox( NULL, strMessage.c_str(), L"XMLPlatformUtils::Initialize()", MB_OK | MB_ICONERROR );
		return 1;
	}


	// COLLADA �t�@�C����ǂݍ���:
	ColladaFile ColladaFile;

	LPTSTR lpColladaFile = DEF_COLLADA_FILE_NAME;
	if( lpCmdLine[0] != L'\0' )	// �t�@�C���̎w�肪����ꍇ
	{
		lpColladaFile = lpCmdLine;
		if( lpColladaFile[0] == L'"' )
		{
			lpColladaFile++;
			lpColladaFile[lstrlen( lpColladaFile ) - 1] = L'\0';
		}
	}

	if( ColladaFile.Load( lpColladaFile ) == false ) { return 1; }

	if( d3dObject.LoadModel( ColladaFile.GetColladaObject() ) == false ) { return 1; }

	d3dObject.SetBackGroundColor( 0xff000080 );


	HACCEL hAccelTable = LoadAccelerators(hInstance, (LPCWSTR)IDC_COLLADAVIEWER);

	// Window�\��:
	ShowWindow( hWnd, nCmdShow );

	d3dObject.ToggleShowDeviceStats();


	MSG msg;
	msg.message = WM_NULL;
	PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );

	while( msg.message != WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) != FALSE )	// ���b�Z�[�W���擾�����ꍇ
		{
			if( TranslateAccelerator( hWnd, hAccelTable, &msg ) == 0 )	// �A�N�Z�����[�^�L�[���������Ȃ������ꍇ
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else	// ���b�Z�[�W���擾���Ȃ������ꍇ
		{
			d3dObject.RenderScene();
		}
	}
	
	xercesc::XMLPlatformUtils::Terminate();	// �N���C�A���g�R�[�h�̍Ō�ɕK�v

	return (int) msg.wParam;
}


//
//  �֐� : MyRegisterClass()
//
//  �ړI : �E�B���h�E �N���X��o�^���܂��B
//
//  �R�����g :
//
//    ���̊֐�����юg�����́A'RegisterClassEx' �֐����ǉ����ꂽ
//     Windows 95 ���O�� Win32 �V�X�e���ƌ݊�������ꍇ�ɂ̂ݕK�v�ł��B
//    �A�v���P�[�V�������A�֘A�t����ꂽ 
//    �������`���̏������A�C�R�����擾�ł���悤�ɂ���ɂ́A
//    ���̊֐����Ăяo���Ă��������B
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_VREDRAW | CS_HREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_COLLADAVIEWER);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName	= (LPCTSTR)IDC_COLLADAVIEWER;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   �֐� : InitInstance(HANDLE, int)
//
//   �ړI : �C���X�^���X �n���h����ۑ����āA���C�� �E�B���h�E���쐬���܂��B
//
//   �R�����g :
//
//        ���̊֐��ŁA�O���[�o���ϐ��ŃC���X�^���X �n���h����ۑ����A
//        ���C�� �v���O���� �E�B���h�E���쐬����ѕ\�����܂��B
//
HWND InitInstance(HINSTANCE hInstance)
{
   hInst = hInstance; // �O���[�o���ϐ��ɃC���X�^���X�������i�[���܂��B

   const DWORD dwStyle = WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_MINIMIZEBOX);

   RECT rc;
   SetRect( &rc, 0, 0, DEF_WINDOW_SIZE_X, DEF_WINDOW_SIZE_Y );
   AdjustWindowRect( &rc, dwStyle, TRUE );

   HWND hWnd = CreateWindow(szWindowClass, szTitle, dwStyle,
	   CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance, NULL);

   return hWnd;
}



void OnKeyDown(WPARAM wVKey)
{
	// ������
}


// �������Ȃ������ꍇ��false��Ԃ�
bool OnCommand(const HWND hWnd, const int iID, const int iEvent)
{
	// �I�����ꂽ���j���[�̉��:
	switch( iID )
	{
	case IDM_ABOUT:
		DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
		return true;
	case IDM_EXIT:
		DestroyWindow( hWnd );
		return true;
	}

	return false;
}


//
//  �֐� : WndProc(HWND, unsigned, WORD, LONG)
//
//  �ړI :  ���C�� �E�B���h�E�̃��b�Z�[�W���������܂��B
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch( uMsg ) 
	{
	case WM_KEYDOWN:
		OnKeyDown( wParam );
		break;

	case WM_COMMAND:
		if( OnCommand( hWnd, LOWORD(wParam), HIWORD(wParam) ) == true ) { return 0; }
		break;

	case WM_EXITSIZEMOVE:
		GetD3DObject().AdjustBackBufferToClient();	// �o�b�N�o�b�t�@�̑傫�����E�B���h�E�ɂ��킹��
		break;

	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = MIN_WINDOW_SIZE_X;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = MIN_WINDOW_SIZE_Y;
		break;

	case WM_ACTIVATEAPP:
		GetD3DObject().SetRenderingPause( wParam == FALSE );	// �A�N�e�B�u�łȂ����͕`����x�߂�
		break;

	case WM_ENTERMENULOOP:
	case WM_EXITMENULOOP:
		GetD3DObject().SetRenderingPause( uMsg == WM_ENTERMENULOOP );	// ���j���[�\�����͕`����x�߂�
		break;

	case WM_NCHITTEST:
		if( GetD3DObject().IsFullScreen() ) { return HTCLIENT; }	// �t���X�N���[���\�����̃��j���[�I���������
		break;

	case WM_SYSCOMMAND:
		switch( wParam )
		{
		case SC_MOVE:
		case SC_SIZE:
		case SC_MAXIMIZE:
		case SC_KEYMENU:
		case SC_MONITORPOWER:
			if( GetD3DObject().IsFullScreen() ) { return 1; }	// �t���X�N���[���\�����̃V�X�e���R�}���h�𖳌��ɂ���
			break;
		}
		break;

	case WM_SYSCHAR:
		switch( wParam )
		{
		case VK_RETURN:
			const DWORD dwAltKey = (1 << 29);
			if( ((DWORD)lParam & dwAltKey) != 0 )	// Alt+Enter�Ńt���X�N���[���؂�ւ�
			{
				GetD3DObject().ToggleFullScreen();              
				return 0;
			}
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


// �o�[�W�������{�b�N�X�̃��b�Z�[�W �n���h���ł��B
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}

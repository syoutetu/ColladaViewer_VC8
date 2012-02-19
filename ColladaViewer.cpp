// ColladaViewer.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include "D3DObject.h"
#include "ColladaFile.h"
#include "ColladaViewer.h"


#define MAX_LOADSTRING 100


#define MIN_WINDOW_SIZE_X	320	// ウィンドウの幅の最小値
#define MIN_WINDOW_SIZE_Y	240	// ウィンドウの高さの最小値
#define DEF_WINDOW_SIZE_X	640	// ウィンドウの幅の標準値
#define DEF_WINDOW_SIZE_Y	480	// ウィンドウの高さの標準値

#define DEF_COLLADA_FILE_NAME	L"collada.dae"	// 標準で読み込むCOLLADAファイル

// グローバル変数 :
HINSTANCE hInst;								// 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];					// タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];			// メイン ウィンドウ クラス名


// このコード モジュールに含まれる関数の宣言を転送します :
ATOM				MyRegisterClass(HINSTANCE hInstance);
HWND				InitInstance(HINSTANCE);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
// xerces側でnewをオーバーロードしているのでコメントアウト
//#if _DEBUG
//	// メモリリークを検査する方法を設定する:
//	int iFlag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );
//
//	iFlag |= _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_EVERY_128_DF;
//
//	_CrtSetDbgFlag( iFlag );
//#endif


	// グローバル文字列を初期化しています。
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_COLLADAVIEWER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// アプリケーションの初期化を実行します。:
	HWND hWnd = InitInstance( hInstance );
	if( hWnd == NULL )
	{
		MessageBox( NULL, L"ウィンドウの作成に失敗しました", L"ウィンドウの作成", MB_OK | MB_ICONERROR );
		return 1;
	}

	// Direct3Dのオブジェクトを作成して初期化する:
	CD3DObject& d3dObject = GetD3DObject();
	if( d3dObject.Initialize( hWnd ) == false )
	{
		MessageBox( NULL, L"Direct3Dオブジェクトの初期化に失敗しました", L"Direct3Dの初期化", MB_OK | MB_ICONERROR );
		return 1;
	}


	try
	{
		xercesc::XMLPlatformUtils::Initialize();	// クライアントコードの最初に必要
	}
	catch( const xercesc::XMLException& ex )
	{
		std::wstring strMessage = L"XMLパーサーの初期化でエラーが発生しました\n\n";
		strMessage += (wchar_t*)ex.getMessage();
		MessageBox( NULL, strMessage.c_str(), L"XMLPlatformUtils::Initialize()", MB_OK | MB_ICONERROR );
		return 1;
	}


	// COLLADA ファイルを読み込む:
	ColladaFile ColladaFile;

	LPTSTR lpColladaFile = DEF_COLLADA_FILE_NAME;
	if( lpCmdLine[0] != L'\0' )	// ファイルの指定がある場合
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

	// Window表示:
	ShowWindow( hWnd, nCmdShow );

	d3dObject.ToggleShowDeviceStats();


	MSG msg;
	msg.message = WM_NULL;
	PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );

	while( msg.message != WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) != FALSE )	// メッセージを取得した場合
		{
			if( TranslateAccelerator( hWnd, hAccelTable, &msg ) == 0 )	// アクセラレータキーを処理しなかった場合
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else	// メッセージを取得しなかった場合
		{
			d3dObject.RenderScene();
		}
	}
	
	xercesc::XMLPlatformUtils::Terminate();	// クライアントコードの最後に必要

	return (int) msg.wParam;
}


//
//  関数 : MyRegisterClass()
//
//  目的 : ウィンドウ クラスを登録します。
//
//  コメント :
//
//    この関数および使い方は、'RegisterClassEx' 関数が追加された
//     Windows 95 より前の Win32 システムと互換させる場合にのみ必要です。
//    アプリケーションが、関連付けられた 
//    正しい形式の小さいアイコンを取得できるようにするには、
//    この関数を呼び出してください。
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
//   関数 : InitInstance(HANDLE, int)
//
//   目的 : インスタンス ハンドルを保存して、メイン ウィンドウを作成します。
//
//   コメント :
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
HWND InitInstance(HINSTANCE hInstance)
{
   hInst = hInstance; // グローバル変数にインスタンス処理を格納します。

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
	// 未実装
}


// 処理しなかった場合はfalseを返す
bool OnCommand(const HWND hWnd, const int iID, const int iEvent)
{
	// 選択されたメニューの解析:
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
//  関数 : WndProc(HWND, unsigned, WORD, LONG)
//
//  目的 :  メイン ウィンドウのメッセージを処理します。
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
		GetD3DObject().AdjustBackBufferToClient();	// バックバッファの大きさをウィンドウにあわせる
		break;

	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = MIN_WINDOW_SIZE_X;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = MIN_WINDOW_SIZE_Y;
		break;

	case WM_ACTIVATEAPP:
		GetD3DObject().SetRenderingPause( wParam == FALSE );	// アクティブでない時は描画を休める
		break;

	case WM_ENTERMENULOOP:
	case WM_EXITMENULOOP:
		GetD3DObject().SetRenderingPause( uMsg == WM_ENTERMENULOOP );	// メニュー表示中は描画を休める
		break;

	case WM_NCHITTEST:
		if( GetD3DObject().IsFullScreen() ) { return HTCLIENT; }	// フルスクリーン表示中のメニュー選択を避ける
		break;

	case WM_SYSCOMMAND:
		switch( wParam )
		{
		case SC_MOVE:
		case SC_SIZE:
		case SC_MAXIMIZE:
		case SC_KEYMENU:
		case SC_MONITORPOWER:
			if( GetD3DObject().IsFullScreen() ) { return 1; }	// フルスクリーン表示中のシステムコマンドを無効にする
			break;
		}
		break;

	case WM_SYSCHAR:
		switch( wParam )
		{
		case VK_RETURN:
			const DWORD dwAltKey = (1 << 29);
			if( ((DWORD)lParam & dwAltKey) != 0 )	// Alt+Enterでフルスクリーン切り替え
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


// バージョン情報ボックスのメッセージ ハンドラです。
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

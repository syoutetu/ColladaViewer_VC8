#include "stdafx.h"

#include "D3DCommon.h"
#include "D3DObject.h"


//#define DEBUG_VS   // 頂点シェーダをデバッグする
//#define DEBUG_PS   // ピクセルシェーダをデバッグする 

#define PERSPECTIVE_FOV		// D3DXMatrixPerspectiveFovLH()を使用する



// ユーザ定義の頂点型を作る
struct CUSTOMVERTEX
{
	FLOAT x, y, z;	// 頂点の座標(x, y, z)
	DWORD color;	// 頂点の色
	FLOAT u, v;		// 頂点のテクスチャ座標(u, v)
};


// マクロ:
#define SETVERTEX(V, _x,_y,_z, _color, _u,_v) {(V).x = _x, (V).y = _y, (V).z = _z, (V).color = _color, (V).u = _u, (V).v =_v;}

// ユーザ定義の頂点型(CUSTOMEVERTEX)のFVFを定義する
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)



// グローバルな静的オブジェクトを取得する
CD3DObject& GetD3DObject()
{
	static CD3DObject d3dObject;
	return d3dObject;
}



CD3DObject::CD3DObject()
{
#ifdef PERSPECTIVE_FOV
	m_fZNear = 0.1f;
	m_fZFar = 10000.0f;
#else
	m_fZNear = 640.0f;
	m_fZFar = 1280.0f;
#endif

	m_fFov = D3DXToRadian(45.0f);

	m_fEyeVec = D3DXVECTOR3( 0.0f, 200.0f, -1000.0f );
	m_fLookAt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_fUpVec = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

	m_pD3D = NULL;
	m_pD3dDevice = NULL;
	m_dwLastTime = 0;

	m_fDisplayWidth = 0.0f;
	m_fDisplayHeight = 0.0f;

	m_hWnd = NULL;
	m_bFullScreen = false;
	m_bDeviceInitialized = false;
	m_bRenderingPaused = false;
	m_bDeviceLost = false;
	m_bShowDeviceStats = false;
	m_bShowBackGround = false;

	m_szDeviceStats[0] = L'\0';
	m_szMovieInfo[0] = L'\0';
	m_lpszFpsStats = m_szDeviceStats;

	m_pD3dFont = NULL;

	m_dwBgColor = 0xff000000;

	m_pD3dTextureBG = NULL;
	m_fBgTextureU = 0.0f;
	m_fBgTextureV = 0.0f;

	m_iMaxTextureHeight = 0;
	m_iMaxTextureWidth = 0;

	m_bPrimBlendOp = false;
	m_bPostPixelShaderBlending = false;

	m_pD3dEffect = NULL;
	m_pD3dModel = NULL;

	InitSettings();
}


CD3DObject::~CD3DObject()
{
	CleanupD3dDevice();

	SAFE_RELEASE(m_pD3D);
}


// 要求する初期設定を行う(デバイスの能力が不足している場合は変更される)
void CD3DObject::InitSettings()
{
	ZeroMemory( &m_D3dPresentParam, sizeof(m_D3dPresentParam) );
	m_D3dDevType = D3DDEVTYPE_HAL;
	m_bCreatePureDevice = true;
	m_dwCreateVertexProcessingFlag = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	m_bEnablePixelShader = false;
	m_PSVersion.iMajor = 1;
	m_PSVersion.iMinor = 1;
	m_bEnableVertexShader = false;
	m_VSVersion.iMajor = 1;
	m_PSVersion.iMinor = 1;

	m_bEnableStencilMask = true;
	m_D3dFormatDepth = D3DFMT_D24S8;

	m_D3dFormatAdapter = D3DFMT_X8R8G8B8;
	m_D3dFormatTexture = D3DFMT_A8R8G8B8;

#ifdef DEBUG_VS
	m_dwCreateVertexProcessingFlag = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
#endif

#ifdef DEBUG_PS
	m_D3dDevType = D3DDEVTYPE_REF;
#endif

}


// フォントオブジェクトを作成する
bool CD3DObject::CreateFont()
{
	_ASSERTE(m_pD3dDevice != NULL);

	SAFE_RELEASE(m_pD3dFont);	// 解放しておく

	HRESULT hr = D3DXCreateFont( m_pD3dDevice, 15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
								DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"ＭＳ ゴシック", &m_pD3dFont );
	if( FAILED(hr) )
	{
		MessageBox( m_hWnd, L"フォントの作成に失敗しました", L"フォントの作成", MB_OK | MB_ICONERROR );
	}

	return SUCCEEDED(hr);
}


// エフェクトオブジェクトを作成する
bool CD3DObject::LoadEffectFile()
{
	_ASSERTE(m_pD3dDevice != NULL);

	SAFE_RELEASE(m_pD3dEffect);	// 解放しておく

	DWORD dwShaderFlags = 0;

#ifdef DEBUG_VS
	dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif

#ifdef DEBUG_PS
	dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif

	WCHAR szEffectFile[MAX_PATH];
	szEffectFile[0] = L'\0';

	GetModuleFileName( NULL, szEffectFile, MAX_PATH );
	PathRemoveFileSpec( szEffectFile );
	StringCchCat( szEffectFile, MAX_PATH, L"\\D3DEffect.fx" );

	// D3DXエフェクトファイルの存在を確認する
	if( PathFileExists( szEffectFile ) == FALSE )
	{
		std::wstring strMessage = L"エフェクトファイル[";
		strMessage += szEffectFile;
		strMessage += L"]が見つかりませんでした";

		MessageBox( m_hWnd, strMessage.c_str(), L"エフェクトファイルの読み込み", MB_OK | MB_ICONERROR );
		return false;
	}

	// エフェクトファイルを読み込む:
	LPD3DXBUFFER pErrorMessage = NULL;	// コンパイルエラーのメッセージを受け取るバッファ
	HRESULT hr = D3DXCreateEffectFromFile( m_pD3dDevice, szEffectFile, NULL, NULL, dwShaderFlags, 
											NULL, &m_pD3dEffect, &pErrorMessage );
	if( FAILED(hr) )
	{
		std::wstring strMessage = L"エフェクトの作成に失敗しました\n";

		if( pErrorMessage != NULL )
		{
			LPCSTR lpszErrorMessage = (LPCSTR)pErrorMessage->GetBufferPointer();

			// マルチバイト文字をワイド文字に変換する:
			WCHAR szError[1024];

			MultiByteToWideChar( CP_ACP, 0, lpszErrorMessage, -1, szError, 1024 );

			szError[1024 - 1] = L'\0';

			strMessage += szError;
		}

		MessageBox( m_hWnd, strMessage.c_str(), L"エフェクトの作成", MB_OK | MB_ICONERROR );
	}

	SAFE_RELEASE(pErrorMessage);

	return SUCCEEDED(hr);
}


void CD3DObject::CleanupD3dDevice()
{
	SAFE_DELETE(m_pD3dModel);

	SAFE_RELEASE(m_pD3dEffect);

	SAFE_RELEASE(m_pD3dFont);

	SAFE_RELEASE(m_pD3dTextureBG);

	if( m_pD3dDevice != NULL )
	{	
		// すべて解放されていることを確認する:
		const ULONG ulRef = m_pD3dDevice->Release();
		_ASSERTE(ulRef == 0);
		m_pD3dDevice = NULL;
	}

	m_bDeviceInitialized = false;
}


void CD3DObject::ResetPresentParam()
{
	_ASSERTE(m_hWnd != NULL);

	ZeroMemory( &m_D3dPresentParam, sizeof(m_D3dPresentParam) );

	m_D3dPresentParam.hDeviceWindow = m_hWnd;

	if( m_bFullScreen )	// フルスクリーンの場合
	{
		m_D3dPresentParam.Windowed = FALSE;
		m_D3dPresentParam.BackBufferWidth = 640;
		m_D3dPresentParam.BackBufferHeight = 480;
		m_D3dPresentParam.FullScreen_RefreshRateInHz = 60;
		m_D3dPresentParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
		m_D3dPresentParam.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
		m_D3dPresentParam.BackBufferFormat = m_D3dFormatAdapter;
	}
	else	// ウィンドウの場合
	{
		m_D3dPresentParam.Windowed = TRUE;
		m_D3dPresentParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
		m_D3dPresentParam.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		m_D3dPresentParam.BackBufferFormat = m_D3dFormatAdapter;
	}

	if( m_bEnableStencilMask )	// 深度バッファを使用する場合
	{		
		m_D3dPresentParam.EnableAutoDepthStencil = m_bEnableStencilMask;
		m_D3dPresentParam.AutoDepthStencilFormat = m_D3dFormatDepth;
	}
}


bool CD3DObject::CreateDevice()
{
	_ASSERTE(m_hWnd != NULL);
	_ASSERTE(m_pD3D != NULL);
	_ASSERTE(m_pD3dDevice == NULL);

	// デバイスの作成前に能力を確認する
	if( ValidateDeviceBeforeCreate() == false ) { return false; }

	ResetPresentParam();

	DWORD dwCreateFlag = m_dwCreateVertexProcessingFlag | (m_bCreatePureDevice ? D3DCREATE_PUREDEVICE : 0);

	if( FAILED(m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, m_D3dDevType, m_hWnd, dwCreateFlag, &m_D3dPresentParam, &m_pD3dDevice )) )	// 失敗した場合
	{
		m_dwCreateVertexProcessingFlag = D3DCREATE_SOFTWARE_VERTEXPROCESSING;	// ソフトウェア頂点処理に変更する
		dwCreateFlag = m_dwCreateVertexProcessingFlag | (m_bCreatePureDevice ? D3DCREATE_PUREDEVICE : 0);

		if( FAILED(m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, m_D3dDevType, m_hWnd, dwCreateFlag, &m_D3dPresentParam, &m_pD3dDevice )) )	// 失敗した場合
		{
			return false;
		}
	}

	return true;
}


bool CD3DObject::ValidateDeviceBeforeCreate()
{
	D3DCAPS9 d3dCaps;
	if( FAILED(m_pD3D->GetDeviceCaps( D3DADAPTER_DEFAULT, m_D3dDevType, &d3dCaps )) )
	{
		MessageBox( m_hWnd, L"デバイスの情報の取得に失敗しました", L"DeviceCapsの取得", MB_OK | MB_ICONERROR );
		return false;
	}

	if( m_bEnablePixelShader == true )	// ピクセルシェーダを使用する場合
	{
		// ピクセルシェーダを使用できるかを調べる
		m_bEnablePixelShader = d3dCaps.PixelShaderVersion >= D3DPS_VERSION(m_PSVersion.iMajor, m_PSVersion.iMinor);
	}

	if( m_bEnableVertexShader == true )	// 頂点シェーダを使用する場合
	{
		// 頂点シェーダを使用できるかを調べる
		m_bEnableVertexShader = d3dCaps.VertexShaderVersion >= D3DVS_VERSION(m_VSVersion.iMajor, m_VSVersion.iMinor);
	}

	// D3DBLENDOP_ADD 以外のアルファブレンディング処理をサポートするかを調べる
	m_bPrimBlendOp = (d3dCaps.PrimitiveMiscCaps & D3DPMISCCAPS_BLENDOP) != 0;

	// デバイスが扱えるテクスチャの大きさの最大値を取得:
	m_iMaxTextureWidth = d3dCaps.MaxTextureWidth;
	m_iMaxTextureHeight = d3dCaps.MaxTextureHeight;
	
	
	// 使用できるバックバッファのフォーマットを探す(バックバッファとアダプタのフォーマットは同じになるように)
	if( FAILED( m_pD3D->CheckDeviceType( D3DADAPTER_DEFAULT, m_D3dDevType, m_D3dFormatAdapter, m_D3dFormatAdapter, m_bFullScreen ? FALSE : TRUE )) )
	{
		m_D3dFormatAdapter = D3DFMT_R5G6B5;	// R5G6B5を使用する

		if( FAILED( m_pD3D->CheckDeviceType( D3DADAPTER_DEFAULT, m_D3dDevType, m_D3dFormatAdapter, m_D3dFormatAdapter, m_bFullScreen ? FALSE : TRUE )) )
		{
			// 両方とも使用できない
			MessageBox( m_hWnd, L"利用できるバックバッファフォーマットが見つかりませんでした", 
						L"バックバッファのフォーマット", MB_OK | MB_ICONERROR );
			return false;
		}			
	}

	// 使用できるテクスチャフォーマットを探す
	if( FAILED(m_pD3D->CheckDeviceFormat( D3DADAPTER_DEFAULT, m_D3dDevType, m_D3dFormatAdapter, 0, D3DRTYPE_TEXTURE, m_D3dFormatTexture )) )
	{
		m_D3dFormatTexture = D3DFMT_A4R4G4B4;	// A4R4G4B4を使用する

		if( FAILED(m_pD3D->CheckDeviceFormat( D3DADAPTER_DEFAULT, m_D3dDevType, m_D3dFormatAdapter, 0, D3DRTYPE_TEXTURE, m_D3dFormatTexture )) )
		{
			// 両方とも使用できない
			MessageBox( m_hWnd, L"利用できるテクスチャフォーマットが見つかりませんでした", 
						L"テクスチャのフォーマット", MB_OK | MB_ICONERROR );
			return false;
		}
	}

	if( m_bEnableStencilMask == true )	// 深度バッファを使用する場合
	{
		// 有効な深度バッファのフォーマットを調べる
		if( FAILED(m_pD3D->CheckDepthStencilMatch( D3DADAPTER_DEFAULT, m_D3dDevType, m_D3dFormatAdapter, m_D3dFormatAdapter, m_D3dFormatDepth )) )
		{
			m_D3dFormatDepth = D3DFMT_D15S1;	// D15S1を使用する

			if( FAILED(m_pD3D->CheckDepthStencilMatch( D3DADAPTER_DEFAULT, m_D3dDevType, m_D3dFormatAdapter, m_D3dFormatAdapter, m_D3dFormatDepth )) )
			{
				// 両方とも使用できない
				m_bEnableStencilMask = false;
			}
		}

		// 深度バッファの互換性を確認する
		if( FAILED(m_pD3D->CheckDepthStencilMatch( D3DADAPTER_DEFAULT, m_D3dDevType, m_D3dFormatAdapter, m_D3dFormatAdapter, m_D3dFormatDepth )) )
		{
			m_bEnableStencilMask = false;
		}
	}

	// ピクセルシェーダ後のアルファブレンディングをサポートするかを調べる
	m_bPostPixelShaderBlending = SUCCEEDED(m_pD3D->CheckDeviceFormat( D3DADAPTER_DEFAULT, m_D3dDevType, m_D3dFormatAdapter,
																	D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING, D3DRTYPE_TEXTURE, m_D3dFormatAdapter )); 

	return true;
}


void CD3DObject::DrawBackGround() const
{
	if( m_pD3dTextureBG == NULL ) { return; }

	_ASSERTE(m_pD3dDevice != NULL);
	_ASSERTE(m_fBgTextureU * m_fBgTextureV != 0.0f);
	_ASSERTE(m_fDisplayWidth * m_fDisplayHeight != 0.0f);

	CUSTOMVERTEX vertex[4];
	SETVERTEX( vertex[0], 0.0f,				0.0f,				0.0f,	0xffffffff, 0.0f,			0.0f );
	SETVERTEX( vertex[1], m_fDisplayWidth,	0.0f,				0.0f,	0xffffffff, m_fBgTextureU,	0.0f );
	SETVERTEX( vertex[2], 0.0f,				m_fDisplayHeight,	0.0f,	0xffffffff, 0.0f,			m_fBgTextureV );
	SETVERTEX( vertex[3], m_fDisplayWidth,	m_fDisplayHeight,	0.0f,	0xffffffff, m_fBgTextureU,	m_fBgTextureV );

	HRESULT hr = S_OK;

	// テクスチャアドレッシングモードの変更（タイル張り状に）:
	VALID(m_pD3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP))
	VALID(m_pD3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP))

	VALID(m_pD3dDevice->SetTexture( 0, m_pD3dTextureBG ))

	VALID(m_pD3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX ))
	VALID(m_pD3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, (LPVOID)vertex, sizeof(CUSTOMVERTEX) ))

	VALID(m_pD3dDevice->SetTexture( 0, NULL ))

	// テクスチャアドレッシングモードを元に戻す
	VALID(m_pD3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP ))
	VALID(m_pD3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP ))
}


void CD3DObject::DrawDeviceStatsString() const
{
	RECT rc;
	SetRect( &rc, 20, 20, m_D3dPresentParam.BackBufferWidth, m_D3dPresentParam.BackBufferHeight );

	m_pD3dFont->DrawTextW( NULL, m_szDeviceStats, -1, &rc, DT_NOCLIP, 0xffffffff );
}


void CD3DObject::DrawMovieInfoString() const
{
	RECT rc;
	SetRect( &rc, 20, 20, m_D3dPresentParam.BackBufferWidth, m_D3dPresentParam.BackBufferHeight );

	HRESULT hr = S_OK;
	VALID(m_pD3dFont->DrawTextW( NULL, m_szMovieInfo, -1, &rc, DT_NOCLIP, 0xffffffff ))
}


void CD3DObject::ShowDeviceValidationMessage() const
{
	_ASSERTE(m_pD3D != NULL);
	_ASSERTE(m_hWnd != NULL);

	std::wstring strMessage;

	if( m_bEnablePixelShader == false )
	{
		WCHAR szTemp[256];
		StringCchPrintf( szTemp, 256, L"現在使用しているデバイスはピクセルシェーダVer%d.%dを扱うことができません\n",
						m_PSVersion.iMajor, m_PSVersion.iMinor );

		strMessage += szTemp;	
	}

	if( m_bEnableVertexShader == false )
	{
		WCHAR szTemp[256];
		StringCchPrintf( szTemp, 256, L"現在使用しているデバイスは頂点シェーダVer%d.%dを扱うことができません\n",
					m_VSVersion.iMajor, m_VSVersion.iMinor );

		strMessage += szTemp;
	}

	if( m_bEnableStencilMask == false )
	{
		strMessage += L"現在使用しているデバイスは深度ステンシルフォーマットを使用することができません\n";
	}

	if( m_bPostPixelShaderBlending == false )
	{
		strMessage += L"現在使用しているデバイスはピクセルシェーダ後のブレンディング処理を使用することができません\n";
	}

	// デバイスが扱えるテクスチャの大きさが512以下の場合は警告:
	if( m_iMaxTextureWidth <= 512 || m_iMaxTextureHeight <= 512 )
	{
		WCHAR szTemp[256];
		StringCchPrintf( szTemp, 256, L"現在使用しているデバイスは幅%dピクセル以下、高さ%dピクセル以下のテクスチャしか扱うことができません\n",
					m_iMaxTextureWidth, m_iMaxTextureHeight );
		strMessage += szTemp;
	}

	if( m_bPrimBlendOp == false )
	{
		strMessage += L"現在使用しているデバイスは「アルファ加算」以外のブレンディング処理をサポートしていません\n";
	}

	if( strMessage.empty() )	// すべてを満たしている場合
	{
		strMessage = L"現在使用しているデバイスはすべての要求を満たしています";
	}

	MessageBox( m_hWnd, strMessage.c_str(), L"デバイス能力の判定", MB_OK | MB_ICONINFORMATION );
}


void CD3DObject::ResetViewProjMatrix()
{
	_ASSERTE(m_fDisplayWidth * m_fDisplayHeight != 0.0f);

	D3DXMATRIXA16 matTemp;

	// 射影行列を設定する:
#ifdef PERSPECTIVE_FOV
	D3DXMatrixPerspectiveFovLH( &matTemp, m_fFov, m_fDisplayWidth / m_fDisplayHeight, m_fZNear, m_fZFar );
#else
	D3DXMatrixPerspectiveLH( &matTemp, m_fDisplayWidth, m_fDisplayHeight, m_fZNear, m_fZFar );
#endif
	m_pD3dDevice->SetTransform( D3DTS_PROJECTION, &matTemp );

	// ビュー行列を設定する:
	D3DXMatrixLookAtLH( &matTemp, &m_fEyeVec, &m_fLookAt, &m_fUpVec );
	m_pD3dDevice->SetTransform( D3DTS_VIEW, &matTemp );
}


void CD3DObject::UpdateDeviceStatsString()
{
	m_szDeviceStats[0] = L'\0';

	_ASSERTE(m_pD3dDevice != NULL);

	if( m_D3dDevType == D3DDEVTYPE_REF )
	{
		StringCchCopy( m_szDeviceStats, dwStatsStringLength, L"REFモード(ソフトウェアシミュレーション)" );
	}
	else
	{
		StringCchCopy( m_szDeviceStats, dwStatsStringLength, L"HALモード(ハードウェアアクセラレーション)" );
	}

	if( (m_dwCreateVertexProcessingFlag == D3DCREATE_HARDWARE_VERTEXPROCESSING) != 0 )
	{
		StringCchCat( m_szDeviceStats, dwStatsStringLength, L" - ハードウェア頂点処理" );
	}
	else if( (m_dwCreateVertexProcessingFlag & D3DCREATE_MIXED_VERTEXPROCESSING) != 0 )
	{
		StringCchCat( m_szDeviceStats, dwStatsStringLength, L" - H/Sミックス頂点処理" );
	}
	else if( (m_dwCreateVertexProcessingFlag & D3DCREATE_SOFTWARE_VERTEXPROCESSING) != 0 )
	{
		StringCchCat( m_szDeviceStats, dwStatsStringLength, L" - ソフトウェア頂点処理" );
	}

	if( m_bCreatePureDevice )
	{
		StringCchCat( m_szDeviceStats, dwStatsStringLength, L"[PureDevice]" );
	}


	D3DADAPTER_IDENTIFIER9 adapterIdentifier;
	if( SUCCEEDED(m_pD3D->GetAdapterIdentifier( D3DADAPTER_DEFAULT, 0, &adapterIdentifier )) )
	{
		StringCchCat( m_szDeviceStats, dwStatsStringLength, L"\nビデオチップ: " );

		// マルチバイト文字をワイド文字に変換する:
		const int iDescLength = sizeof(adapterIdentifier.Description) / sizeof(adapterIdentifier.Description[0]);
		WCHAR szDescription[iDescLength];

		MultiByteToWideChar( CP_ACP, 0, adapterIdentifier.Description, -1, szDescription, iDescLength );

		szDescription[iDescLength - 1] = L'\0';
		
		StringCchCat( m_szDeviceStats, dwStatsStringLength, szDescription );
	}

	StringCchCat( m_szDeviceStats, dwStatsStringLength, L"\nバックバッファ フォーマット: " );

	if( m_D3dPresentParam.BackBufferFormat == D3DFMT_X8R8G8B8 )
	{
		StringCchCat( m_szDeviceStats, dwStatsStringLength, L"X8R8G8B8" );
	}
	else if( m_D3dPresentParam.BackBufferFormat == D3DFMT_R5G6B5 )
	{
		StringCchCat( m_szDeviceStats, dwStatsStringLength, L"R5G6B5" );
	}

	WCHAR szBackBufferSize[256];
	StringCchPrintf( szBackBufferSize, 256, L" - %d X %d", m_D3dPresentParam.BackBufferWidth, m_D3dPresentParam.BackBufferHeight );
	szBackBufferSize[256 - 1] = L'\0';
	StringCchCat( m_szDeviceStats, dwStatsStringLength, szBackBufferSize );

	StringCchCat( m_szDeviceStats, dwStatsStringLength, L"\nテクスチャ フォーマット: " );
	if( m_D3dFormatTexture == D3DFMT_A8R8G8B8 )
	{
		StringCchCat( m_szDeviceStats, dwStatsStringLength, L"A8R8G8B8" );
	}
	else if( m_D3dFormatTexture == D3DFMT_A4R4G4B4 )
	{
		StringCchCat( m_szDeviceStats, dwStatsStringLength, L"A4R4G4B4" );
	}

	// FPS表示の位置を設定する:
	size_t stLength = 0;
	StringCchLength( m_szDeviceStats, dwStatsStringLength, &stLength );
	m_lpszFpsStats = m_szDeviceStats + stLength;
}


void CD3DObject::UpdateFpsStatsString()
{
	static int iCount = 0;	// 1秒間に描画された回数
	static DWORD dwLastTime = 0;	// 最後に更新した時間
	
	const DWORD dwNowTime = GetTickCount();

	// 1秒間で更新する
	if( dwNowTime - dwLastTime >= 1000 )
	{
		const DWORD dwLastLength = dwStatsStringLength - (DWORD)(m_lpszFpsStats - m_szDeviceStats);
		_ASSERTE(IsBadWritePtr( m_lpszFpsStats, dwLastLength ) == FALSE);

		const FLOAT fFramePerSec = (FLOAT)(iCount * 1000) / (dwNowTime - dwLastTime);

		StringCchPrintf( m_lpszFpsStats, dwLastLength, L"\n%.1f フレーム / 秒", fFramePerSec );

		dwLastTime = dwNowTime;
		iCount = 0;
	}
	else
	{
		iCount++;
	}
}


void CD3DObject::InitDeviceStats()
{
	if( m_bDeviceInitialized == false ) { return; }	// まだ初期化されていない場合

	HRESULT hr = S_OK;

	// カリングを無効にする
//	VALID(m_pD3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE));

    // ライティングを有効にする
    VALID(m_pD3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE));
	VALID(m_pD3dDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020));

	// シェーディング方法を設定する
	VALID(m_pD3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD));

	// クリッピングを無効にする
	VALID(m_pD3dDevice->SetRenderState(D3DRS_CLIPPING, FALSE));

	// 深度バッファを利用しない場合はZバッファを無効にする
	if( m_bEnableStencilMask == false ) { VALID(m_pD3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE)); }

	// テクスチャのアルファ関連の設定 : 描画色のA値が不透明度になるように設定:
	VALID(m_pD3dDevice->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_MODULATE));
	VALID(m_pD3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE));
	VALID(m_pD3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE));
	VALID(m_pD3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE));
	VALID(m_pD3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE));
	VALID(m_pD3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE));
	VALID(m_pD3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE));
	VALID(m_pD3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA ));
	VALID(m_pD3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA));
	
	// テクスチャサンプリングモードを設定:
	VALID(m_pD3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP ));
	VALID(m_pD3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP ));
	VALID(m_pD3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR ));
	VALID(m_pD3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR ));
}


void CD3DObject::OnLostDevice()
{
	if( m_pD3dEffect != NULL ) { m_pD3dEffect->OnLostDevice(); }

	if( m_pD3dFont != NULL ) { m_pD3dFont->OnLostDevice(); }
}


void CD3DObject::OnResetDevice()
{
	if( m_pD3dEffect != NULL ) { m_pD3dEffect->OnResetDevice(); }

	if( m_pD3dFont != NULL ) { m_pD3dFont->OnResetDevice(); }
}


bool CD3DObject::Reset3DEnvironment()
{
	OnLostDevice();	// デバイスが消失した時の処理

	HRESULT hr = m_pD3dDevice->Reset( &m_D3dPresentParam );
	while( FAILED(hr) )
	{
		// TestCooperativeLevel()がD3DERR_DEVICENOTRESETを返すまで待機:
		hr = m_pD3dDevice->TestCooperativeLevel();
		switch( hr )
		{
		case D3DERR_DEVICELOST:

			Sleep(100);	// デバイスが消失したので待機する
			break;

		case D3DERR_DEVICENOTRESET:

			m_bDeviceLost = true;	// デバイスが消失状態
		// 必要ないかもしれない	OnLostDevice();	// デバイスが消失した時の処理

			hr = m_pD3dDevice->Reset( &m_D3dPresentParam );
			if( FAILED(hr) )	// リセットできなかった場合
			{
				MessageBox( m_hWnd, L"デバイスのリセットに失敗しました", L"デバイスの消失", MB_OK | MB_ICONERROR );
				VALID_RETURN(hr);
			}
			break;
		}	//-----switch( m_pd3dDevice->TestCooperativeLevel() )-----
	}	//-----while( FAILED(hr) )-----

	OnResetDevice();	// デバイスをリセットした時の処理

	InitDeviceStats();	// デバイスの状態を設定する

	ResetTimer();	// タイマーをリセットする

	UpdateDeviceStatsString();	// デバイスの情報を更新する

	ResetViewProjMatrix();	// ビュー行列と、射影行列をリセットする

	m_bDeviceLost = false;	// デバイス消失状態を設定する

	return true;
}



bool CD3DObject::Initialize(HWND hWnd)
{
	if( m_pD3D == NULL )	// D3Dオブジェクトがまだ作成されていない場合
	{
		// D3DXのバージョンを確認する
		if( D3DXCheckVersion( D3D_SDK_VERSION, D3DX_SDK_VERSION ) == FALSE )
		{
			MessageBox( m_hWnd, L"DirectXのバージョンが違います。新しいDirectXをインストールしてください",
				L"DirectXのバージョン確認", MB_OK | MB_ICONERROR );
			return false;
		}

		// Direct3Dオブジェクトを作成する
		m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
		if( m_pD3D == NULL )
		{
			MessageBox( m_hWnd, L"Direct3Dオブジェクトの作成に失敗しました",
				L"Direct3Dオブジェクトの作成", MB_OK | MB_ICONERROR );
			return false;
		}
	}

	if( m_bDeviceInitialized == false )	// まだ初期化されていない場合
	{
		_ASSERTE(m_hWnd == NULL);
		m_hWnd = hWnd;	// ウィンドウを設定する

		_ASSERTE(m_pD3dDevice == NULL);

		InitSettings();	// 設定を初期化する

		// Direct3Dデバイスを作成する
		if( CreateDevice() == false )	// 失敗した場合
		{
			InitSettings();	// 設定を初期化する
			m_bCreatePureDevice = false;	// D3DCREATE_PUREDEVICEをOFFにして作成する

			if( CreateDevice() == false )	// さらに失敗した場合
			{
				InitSettings();	// 設定を初期化する
				m_bCreatePureDevice = false;	// D3DCREATE_PUREDEVICEをOFFにして作成する
				m_D3dDevType = D3DDEVTYPE_REF;	// REFモードでデバイスを作成する

				if( CreateDevice() == false )	// それでも失敗した場合
				{
					MessageBox( m_hWnd, L"Direct3Dデバイスの作成に失敗しました",
						L"Direct3Dデバイスの作成", MB_OK | MB_ICONERROR );
					return false;
				}
			}
		}

		if( m_D3dDevType == D3DDEVTYPE_REF )	// REFモードで作成した場合はメッセージを表示する
		{
			MessageBox( m_hWnd, L"Direct3DデバイスをREFモードで作成しました。動作は非常に遅くなります",
				L"Direct3Dデバイスの作成", MB_OK | MB_ICONWARNING );
		}

		if( CreateFont() == false ) { return false; }	// フォントを作成する
		//未実装 if( LoadEffectFile() == false ) { return false; }	// エフェクトファイルを読み込む

		AdjustDisplayToBackBuffer();	// ディスプレイ領域のデフォルトはバックバッファの領域にする

		m_bDeviceInitialized = true;
	}

	_ASSERTE(m_pD3dDevice != NULL);
	_ASSERTE(m_hWnd == hWnd);	// 最初に初期化した時と違うウィンドウが指定された

	const bool bReset = Reset3DEnvironment();	// 3D環境をリセットする
	_ASSERTE(bReset == true);

	return bReset;
}


void CD3DObject::SetDisplayWidthHeight(const FLOAT fWidth, const FLOAT fHeight)
{
	if( fWidth * fHeight == 0.0f ) { return; }

	m_fDisplayWidth = fWidth;
	m_fDisplayHeight = fHeight;

	ResetViewProjMatrix();	// ビュー行列と射影行列を更新する
}


void CD3DObject::AdjustDisplayToBackBuffer()
{
	_ASSERTE(m_D3dPresentParam.BackBufferWidth * m_D3dPresentParam.BackBufferHeight > 0);

	m_fDisplayWidth = (FLOAT)m_D3dPresentParam.BackBufferWidth;
	m_fDisplayHeight = (FLOAT)m_D3dPresentParam.BackBufferHeight;

	ResetViewProjMatrix();	// ビュー行列と射影行列を更新する
}


bool CD3DObject::LoadBackGroundTexture(LPCWSTR lpszFileName)
{
	_ASSERTE(m_pD3dDevice != NULL);
	_ASSERTE(IsBadStringPtr( lpszFileName, MAX_PATH ) == FALSE);

	if( PathFileExists( lpszFileName ) == FALSE ) { return false; }

	SAFE_RELEASE(m_pD3dTextureBG);	// 解放しておく

	HRESULT hr = S_OK;

	D3DXIMAGE_INFO d3DImageInfo;
	VALID_RETURN(D3DXCreateTextureFromFileEx( m_pD3dDevice, lpszFileName, D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_UNKNOWN, 
											D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, &d3DImageInfo, NULL, &m_pD3dTextureBG ));

	D3DSURFACE_DESC d3DSurfaceDesc;
	VALID_RETURN(m_pD3dTextureBG->GetLevelDesc( 0, &d3DSurfaceDesc ));

	// U,V座標を計算する:
	m_fBgTextureU = (FLOAT)d3DImageInfo.Width / d3DSurfaceDesc.Width;
	m_fBgTextureV = (FLOAT)d3DImageInfo.Height / d3DSurfaceDesc.Height;

	m_bShowBackGround = true;

	return true;
}


void CD3DObject::AdjustBackBufferToClient()
{
	_ASSERTE(m_hWnd != NULL);

	RECT rc;
	if( GetClientRect( m_hWnd, &rc ) == FALSE ) { return; }

	const UINT uiClientWidth = (UINT)(rc.right - rc.left);
	const UINT uiClientHeight = (UINT)(rc.bottom - rc.top);

	// サイズが違う場合はバックバッファのサイズを変更してリセットする
	if( m_D3dPresentParam.BackBufferWidth != uiClientWidth ||
		m_D3dPresentParam.BackBufferHeight != uiClientHeight )
	{
		m_D3dPresentParam.BackBufferWidth = uiClientWidth;
		m_D3dPresentParam.BackBufferHeight = uiClientHeight;

		Reset3DEnvironment();
	}
}


void CD3DObject::ToggleFullScreen()
{
	SetRenderingPause( true );

	// 未実装
    
	SetRenderingPause( false );
}



void CD3DObject::RenderScene()
{
	_ASSERTE(m_bDeviceInitialized == true);
	_ASSERTE(m_hWnd != NULL);

	HRESULT hr = S_OK;

	if( m_bRenderingPaused ) { Sleep( 100 ); }	// 停止状態の時はCPUが他の処理をできるようにする
	if( m_bDeviceLost ) { return; }	// デバイスが消失状態の時は描画しない


	const DWORD dwClearFlag = D3DCLEAR_TARGET | (m_bEnableStencilMask ? D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL : 0);

	VALID(m_pD3dDevice->Clear(0, NULL, dwClearFlag, m_dwBgColor, 1.0f, 0));

	if( SUCCEEDED(m_pD3dDevice->BeginScene()) )
	{
		// ワールド行列を初期化する:
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity( &matWorld );
		m_pD3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

		if( m_bShowBackGround )	// 背景を表示する場合
		{
			DrawBackGround();
		}

		if( m_pD3dModel != NULL )	// モデルデータが読み込まれている場合
		{
			m_pD3dModel->Show( m_pD3dDevice );	// モデルデータを表示する
		}

		if( m_bShowDeviceStats )	// デバイス情報を表示する場合
		{
			UpdateFpsStatsString();	// FPSを更新する
			DrawDeviceStatsString();
		}

		m_pD3dDevice->EndScene();

		hr = m_pD3dDevice->Present( NULL, NULL, NULL, NULL );
		if( FAILED(hr ) )
		{
			if( hr == D3DERR_DEVICELOST ) { m_bDeviceLost = true; }	// デバイスが消失状態

			VALID(hr);	// デバッグ時にエラーメッセージを表示する

			Reset3DEnvironment();	// 描画環境をリセットする
		}
	}
}



bool CD3DObject::LoadModel(ColladaObject* pColladaObj)
{
	_ASSERTE(m_pD3dDevice != NULL);
	_ASSERTE(pColladaObj != NULL);

	SAFE_DELETE(m_pD3dModel);	// 解放しておく

	m_pD3dModel = new D3DModel();

	if( m_pD3dModel->Read( m_pD3dDevice, pColladaObj ) == false )
	{
		std::wstring strMessage = L"モデルデータを作成中にエラーが発生しました";
		MessageBox( NULL, strMessage.c_str(), L"CD3DObject::LoadModel", MB_OK | MB_ICONERROR );
		return false;
	}

	return true;
}

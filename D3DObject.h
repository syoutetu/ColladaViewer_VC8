#pragma once

#if !defined ___D3DObject_h___
#define ___D3DObject_h___


#include "D3DModel.h"


class CD3DObject
{
private:

	FLOAT m_fZNear;
	FLOAT m_fZFar;
	FLOAT m_fFov;

	D3DXVECTOR3 m_fEyeVec;
	D3DXVECTOR3 m_fLookAt;
    D3DXVECTOR3 m_fUpVec;

	struct ShaderVersion
	{
		int iMajor;
		int iMinor;
	};

	LPDIRECT3D9	m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3dDevice;
	DWORD	m_dwLastTime;

	LPD3DXFONT	m_pD3dFont;	// テキスト情報を表示するフォントオブジェクト
	
	static const DWORD	dwStatsStringLength = 1024;	// テキスト情報の文字列の長さ
	WCHAR	m_szDeviceStats[dwStatsStringLength];	// デバイス状態を表示する文字列
	WCHAR	m_szMovieInfo[dwStatsStringLength];		// ムービー情報を表示する文字列
	
	LPTSTR	m_lpszFpsStats;	// FPS情報を表示する文字列の位置(m_szDeviceStatsの一部を使用する)

	DWORD	m_dwBgColor;	// 背景色

	LPDIRECT3DTEXTURE9	m_pD3dTextureBG;	// 背景に使用するテクスチャ
	FLOAT	m_fBgTextureU;	// 背景に使用するテクスチャU座標の幅
	FLOAT	m_fBgTextureV;	// 背景に使用するテクスチャV座標の高さ

	FLOAT	m_fDisplayWidth;	// 表示する領域の幅
	FLOAT	m_fDisplayHeight;	// 表示する領域の高さ

	HWND	m_hWnd;		// ターゲットウィンドウ
	bool	m_bFullScreen;			// フルスクリーン表示
	bool	m_bDeviceInitialized;	// デバイスが初期化された
	bool	m_bRenderingPaused;		// レンダリングが停止された
	bool	m_bDeviceLost;			// デバイスが消失状態

	bool	m_bShowDeviceStats;		// デバイス状態のテキストを表示する
	bool	m_bShowBackGround;		// 背景を表示する


	// 要求するデバイスの設定(デバイスの能力が不足した場合は変更される):
	D3DPRESENT_PARAMETERS	m_D3dPresentParam;
	D3DDEVTYPE	m_D3dDevType;
	bool	m_bCreatePureDevice;			// CreateDeviceで設定するPUREDEVICEのフラグ
	DWORD	m_dwCreateVertexProcessingFlag;	// CreateDeviceで設定するVERTEXPROCESSINGのフラグ
	
	bool	m_bEnablePixelShader;	// ピクセルシェーダが使用できる
	ShaderVersion	m_PSVersion;	// ピクセルシェーダのバージョン
	bool	m_bEnableVertexShader;	// 頂点シェーダが使用できる
	ShaderVersion	m_VSVersion;	// 頂点シェーダのバージョン
	
	bool	m_bEnableStencilMask;	// 深度バッファが使用できる
	D3DFORMAT	m_D3dFormatDepth;	// 深度バッファのフォーマット

	D3DFORMAT	m_D3dFormatAdapter;	// アダプタディスプレイのフォーマット
	D3DFORMAT	m_D3dFormatTexture;	// テクスチャのフォーマット

	bool	m_bPrimBlendOp;				// D3DBLENDOP_ADD 以外のアルファブレンディング処理をサポートする
	bool	m_bPostPixelShaderBlending;	// ピクセルシェーダ後のアルファブレンディングをサポートする
	int		m_iMaxTextureWidth;			// 使用できる最大のテクスチャの幅
	int		m_iMaxTextureHeight;		// 使用できる最大のテクスチャの高さ


	LPD3DXEFFECT	m_pD3dEffect;	// エフェクトオブジェクト
	D3DModel*		m_pD3dModel;	// モデルオブジェクト


	void InitSettings();	// 要求する初期設定を行う

	bool CreateFont();	// フォントを作成する
	bool LoadEffectFile();	// エフェクトファイルを読み込む

	void CleanupD3dDevice();	// D3DDeviceを解放する

	void ResetPresentParam();	// D3DPRESENT_PARAMETERS構造体を設定する

	bool CreateDevice();	// デバイスを作成する

	bool ValidateDeviceBeforeCreate();	// デバイスの作成前に設定を確認する処理

	void DrawBackGround() const;	// 背景を描画する

	void DrawDeviceStatsString() const;	// デバイス状態のテキストを描画する
	void DrawMovieInfoString() const;	// ムービー情報のテキストを描画する

	void ShowDeviceValidationMessage() const;	// デバイスの能力に関する報告を表示する

	void ResetViewProjMatrix();	// ビュー行列と射影行列をリセットする

	void UpdateDeviceStatsString();	// デバイスの情報を更新する
	void UpdateFpsStatsString();	// フレームレートの情報を更新する

	void InitDeviceStats();	// デバイスを再設定する時の処理

	void OnResetDevice();	// デバイスがリセットされた時の処理
	void OnLostDevice();	// デバイスが消失した時の処理

	bool Reset3DEnvironment();	// 3D環境をリセットする

public:

	CD3DObject();

	~CD3DObject();


	LPDIRECT3DDEVICE9 GetD3dDevice() const	{ _ASSERTE(m_pD3dDevice != NULL); return m_pD3dDevice; }

	bool Is16bitTextureFormat() const	{ return m_D3dFormatTexture == D3DFMT_A4R4G4B4; }

	bool IsDeviceInitialized() const	{ return m_bDeviceInitialized; }

	bool IsFullScreen() const	{ return m_bFullScreen; }

	void SetRenderingPause(bool bPause)	{ m_bRenderingPaused = bPause; }

	void ToggleShowDeviceStats()	{ m_bShowDeviceStats = !m_bShowDeviceStats; }
	void ToggleShowBackGround()	{ m_bShowBackGround = !m_bShowBackGround; }

	bool Initialize(HWND hWnd);	// デバイスを初期化する

	FLOAT GetDisplayWidth() const	{ return m_fDisplayWidth; }
	FLOAT GetDisplayHeight() const	{ return m_fDisplayHeight; }

	void SetDisplayWidthHeight(const FLOAT fWidth, const FLOAT fHeight);	// ディスプレイの領域を設定する
	void AdjustDisplayToBackBuffer();	// ディスプレイの領域をバックバッファの領域にあわせる

	void SetBackGroundColor(const DWORD dwColor)	{ m_dwBgColor = dwColor; }	// 背景色を設定する

	bool LoadBackGroundTexture(LPCWSTR lpszFileName);	// 背景に使用する画像を読み込む

	void ResetTimer()	{ m_dwLastTime = GetTickCount(); }	// 経過時間を取得するタイマーをリセットする 
	DWORD GetElapsedTime() const	{ return GetTickCount() - m_dwLastTime; }	// リセットした時からの経過時間を取得する(単位:ミリセカンド)

	void AdjustBackBufferToClient();	// バックバッファの範囲をウィンドウのクライアント範囲にあわせる

	void ToggleFullScreen();	// フルスクリーン切り替え

	void RenderScene();	// 描画する

	bool LoadModel(ColladaObject* pColladaObj);
};



CD3DObject& GetD3DObject();	// グローバルな静的オブジェクトを取得する


#endif	//___D3DObject_h___

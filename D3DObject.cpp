#include "stdafx.h"

#include "D3DCommon.h"
#include "D3DObject.h"


//#define DEBUG_VS   // ���_�V�F�[�_���f�o�b�O����
//#define DEBUG_PS   // �s�N�Z���V�F�[�_���f�o�b�O���� 

#define PERSPECTIVE_FOV		// D3DXMatrixPerspectiveFovLH()���g�p����



// ���[�U��`�̒��_�^�����
struct CUSTOMVERTEX
{
	FLOAT x, y, z;	// ���_�̍��W(x, y, z)
	DWORD color;	// ���_�̐F
	FLOAT u, v;		// ���_�̃e�N�X�`�����W(u, v)
};


// �}�N��:
#define SETVERTEX(V, _x,_y,_z, _color, _u,_v) {(V).x = _x, (V).y = _y, (V).z = _z, (V).color = _color, (V).u = _u, (V).v =_v;}

// ���[�U��`�̒��_�^(CUSTOMEVERTEX)��FVF���`����
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)



// �O���[�o���ȐÓI�I�u�W�F�N�g���擾����
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


// �v�����鏉���ݒ���s��(�f�o�C�X�̔\�͂��s�����Ă���ꍇ�͕ύX�����)
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


// �t�H���g�I�u�W�F�N�g���쐬����
bool CD3DObject::CreateFont()
{
	_ASSERTE(m_pD3dDevice != NULL);

	SAFE_RELEASE(m_pD3dFont);	// ������Ă���

	HRESULT hr = D3DXCreateFont( m_pD3dDevice, 15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
								DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"�l�r �S�V�b�N", &m_pD3dFont );
	if( FAILED(hr) )
	{
		MessageBox( m_hWnd, L"�t�H���g�̍쐬�Ɏ��s���܂���", L"�t�H���g�̍쐬", MB_OK | MB_ICONERROR );
	}

	return SUCCEEDED(hr);
}


// �G�t�F�N�g�I�u�W�F�N�g���쐬����
bool CD3DObject::LoadEffectFile()
{
	_ASSERTE(m_pD3dDevice != NULL);

	SAFE_RELEASE(m_pD3dEffect);	// ������Ă���

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

	// D3DX�G�t�F�N�g�t�@�C���̑��݂��m�F����
	if( PathFileExists( szEffectFile ) == FALSE )
	{
		std::wstring strMessage = L"�G�t�F�N�g�t�@�C��[";
		strMessage += szEffectFile;
		strMessage += L"]��������܂���ł���";

		MessageBox( m_hWnd, strMessage.c_str(), L"�G�t�F�N�g�t�@�C���̓ǂݍ���", MB_OK | MB_ICONERROR );
		return false;
	}

	// �G�t�F�N�g�t�@�C����ǂݍ���:
	LPD3DXBUFFER pErrorMessage = NULL;	// �R���p�C���G���[�̃��b�Z�[�W���󂯎��o�b�t�@
	HRESULT hr = D3DXCreateEffectFromFile( m_pD3dDevice, szEffectFile, NULL, NULL, dwShaderFlags, 
											NULL, &m_pD3dEffect, &pErrorMessage );
	if( FAILED(hr) )
	{
		std::wstring strMessage = L"�G�t�F�N�g�̍쐬�Ɏ��s���܂���\n";

		if( pErrorMessage != NULL )
		{
			LPCSTR lpszErrorMessage = (LPCSTR)pErrorMessage->GetBufferPointer();

			// �}���`�o�C�g���������C�h�����ɕϊ�����:
			WCHAR szError[1024];

			MultiByteToWideChar( CP_ACP, 0, lpszErrorMessage, -1, szError, 1024 );

			szError[1024 - 1] = L'\0';

			strMessage += szError;
		}

		MessageBox( m_hWnd, strMessage.c_str(), L"�G�t�F�N�g�̍쐬", MB_OK | MB_ICONERROR );
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
		// ���ׂĉ������Ă��邱�Ƃ��m�F����:
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

	if( m_bFullScreen )	// �t���X�N���[���̏ꍇ
	{
		m_D3dPresentParam.Windowed = FALSE;
		m_D3dPresentParam.BackBufferWidth = 640;
		m_D3dPresentParam.BackBufferHeight = 480;
		m_D3dPresentParam.FullScreen_RefreshRateInHz = 60;
		m_D3dPresentParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
		m_D3dPresentParam.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
		m_D3dPresentParam.BackBufferFormat = m_D3dFormatAdapter;
	}
	else	// �E�B���h�E�̏ꍇ
	{
		m_D3dPresentParam.Windowed = TRUE;
		m_D3dPresentParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
		m_D3dPresentParam.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		m_D3dPresentParam.BackBufferFormat = m_D3dFormatAdapter;
	}

	if( m_bEnableStencilMask )	// �[�x�o�b�t�@���g�p����ꍇ
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

	// �f�o�C�X�̍쐬�O�ɔ\�͂��m�F����
	if( ValidateDeviceBeforeCreate() == false ) { return false; }

	ResetPresentParam();

	DWORD dwCreateFlag = m_dwCreateVertexProcessingFlag | (m_bCreatePureDevice ? D3DCREATE_PUREDEVICE : 0);

	if( FAILED(m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, m_D3dDevType, m_hWnd, dwCreateFlag, &m_D3dPresentParam, &m_pD3dDevice )) )	// ���s�����ꍇ
	{
		m_dwCreateVertexProcessingFlag = D3DCREATE_SOFTWARE_VERTEXPROCESSING;	// �\�t�g�E�F�A���_�����ɕύX����
		dwCreateFlag = m_dwCreateVertexProcessingFlag | (m_bCreatePureDevice ? D3DCREATE_PUREDEVICE : 0);

		if( FAILED(m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, m_D3dDevType, m_hWnd, dwCreateFlag, &m_D3dPresentParam, &m_pD3dDevice )) )	// ���s�����ꍇ
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
		MessageBox( m_hWnd, L"�f�o�C�X�̏��̎擾�Ɏ��s���܂���", L"DeviceCaps�̎擾", MB_OK | MB_ICONERROR );
		return false;
	}

	if( m_bEnablePixelShader == true )	// �s�N�Z���V�F�[�_���g�p����ꍇ
	{
		// �s�N�Z���V�F�[�_���g�p�ł��邩�𒲂ׂ�
		m_bEnablePixelShader = d3dCaps.PixelShaderVersion >= D3DPS_VERSION(m_PSVersion.iMajor, m_PSVersion.iMinor);
	}

	if( m_bEnableVertexShader == true )	// ���_�V�F�[�_���g�p����ꍇ
	{
		// ���_�V�F�[�_���g�p�ł��邩�𒲂ׂ�
		m_bEnableVertexShader = d3dCaps.VertexShaderVersion >= D3DVS_VERSION(m_VSVersion.iMajor, m_VSVersion.iMinor);
	}

	// D3DBLENDOP_ADD �ȊO�̃A���t�@�u�����f�B���O�������T�|�[�g���邩�𒲂ׂ�
	m_bPrimBlendOp = (d3dCaps.PrimitiveMiscCaps & D3DPMISCCAPS_BLENDOP) != 0;

	// �f�o�C�X��������e�N�X�`���̑傫���̍ő�l���擾:
	m_iMaxTextureWidth = d3dCaps.MaxTextureWidth;
	m_iMaxTextureHeight = d3dCaps.MaxTextureHeight;
	
	
	// �g�p�ł���o�b�N�o�b�t�@�̃t�H�[�}�b�g��T��(�o�b�N�o�b�t�@�ƃA�_�v�^�̃t�H�[�}�b�g�͓����ɂȂ�悤��)
	if( FAILED( m_pD3D->CheckDeviceType( D3DADAPTER_DEFAULT, m_D3dDevType, m_D3dFormatAdapter, m_D3dFormatAdapter, m_bFullScreen ? FALSE : TRUE )) )
	{
		m_D3dFormatAdapter = D3DFMT_R5G6B5;	// R5G6B5���g�p����

		if( FAILED( m_pD3D->CheckDeviceType( D3DADAPTER_DEFAULT, m_D3dDevType, m_D3dFormatAdapter, m_D3dFormatAdapter, m_bFullScreen ? FALSE : TRUE )) )
		{
			// �����Ƃ��g�p�ł��Ȃ�
			MessageBox( m_hWnd, L"���p�ł���o�b�N�o�b�t�@�t�H�[�}�b�g��������܂���ł���", 
						L"�o�b�N�o�b�t�@�̃t�H�[�}�b�g", MB_OK | MB_ICONERROR );
			return false;
		}			
	}

	// �g�p�ł���e�N�X�`���t�H�[�}�b�g��T��
	if( FAILED(m_pD3D->CheckDeviceFormat( D3DADAPTER_DEFAULT, m_D3dDevType, m_D3dFormatAdapter, 0, D3DRTYPE_TEXTURE, m_D3dFormatTexture )) )
	{
		m_D3dFormatTexture = D3DFMT_A4R4G4B4;	// A4R4G4B4���g�p����

		if( FAILED(m_pD3D->CheckDeviceFormat( D3DADAPTER_DEFAULT, m_D3dDevType, m_D3dFormatAdapter, 0, D3DRTYPE_TEXTURE, m_D3dFormatTexture )) )
		{
			// �����Ƃ��g�p�ł��Ȃ�
			MessageBox( m_hWnd, L"���p�ł���e�N�X�`���t�H�[�}�b�g��������܂���ł���", 
						L"�e�N�X�`���̃t�H�[�}�b�g", MB_OK | MB_ICONERROR );
			return false;
		}
	}

	if( m_bEnableStencilMask == true )	// �[�x�o�b�t�@���g�p����ꍇ
	{
		// �L���Ȑ[�x�o�b�t�@�̃t�H�[�}�b�g�𒲂ׂ�
		if( FAILED(m_pD3D->CheckDepthStencilMatch( D3DADAPTER_DEFAULT, m_D3dDevType, m_D3dFormatAdapter, m_D3dFormatAdapter, m_D3dFormatDepth )) )
		{
			m_D3dFormatDepth = D3DFMT_D15S1;	// D15S1���g�p����

			if( FAILED(m_pD3D->CheckDepthStencilMatch( D3DADAPTER_DEFAULT, m_D3dDevType, m_D3dFormatAdapter, m_D3dFormatAdapter, m_D3dFormatDepth )) )
			{
				// �����Ƃ��g�p�ł��Ȃ�
				m_bEnableStencilMask = false;
			}
		}

		// �[�x�o�b�t�@�̌݊������m�F����
		if( FAILED(m_pD3D->CheckDepthStencilMatch( D3DADAPTER_DEFAULT, m_D3dDevType, m_D3dFormatAdapter, m_D3dFormatAdapter, m_D3dFormatDepth )) )
		{
			m_bEnableStencilMask = false;
		}
	}

	// �s�N�Z���V�F�[�_��̃A���t�@�u�����f�B���O���T�|�[�g���邩�𒲂ׂ�
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

	// �e�N�X�`���A�h���b�V���O���[�h�̕ύX�i�^�C�������Ɂj:
	VALID(m_pD3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP))
	VALID(m_pD3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP))

	VALID(m_pD3dDevice->SetTexture( 0, m_pD3dTextureBG ))

	VALID(m_pD3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX ))
	VALID(m_pD3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, (LPVOID)vertex, sizeof(CUSTOMVERTEX) ))

	VALID(m_pD3dDevice->SetTexture( 0, NULL ))

	// �e�N�X�`���A�h���b�V���O���[�h�����ɖ߂�
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
		StringCchPrintf( szTemp, 256, L"���ݎg�p���Ă���f�o�C�X�̓s�N�Z���V�F�[�_Ver%d.%d���������Ƃ��ł��܂���\n",
						m_PSVersion.iMajor, m_PSVersion.iMinor );

		strMessage += szTemp;	
	}

	if( m_bEnableVertexShader == false )
	{
		WCHAR szTemp[256];
		StringCchPrintf( szTemp, 256, L"���ݎg�p���Ă���f�o�C�X�͒��_�V�F�[�_Ver%d.%d���������Ƃ��ł��܂���\n",
					m_VSVersion.iMajor, m_VSVersion.iMinor );

		strMessage += szTemp;
	}

	if( m_bEnableStencilMask == false )
	{
		strMessage += L"���ݎg�p���Ă���f�o�C�X�͐[�x�X�e���V���t�H�[�}�b�g���g�p���邱�Ƃ��ł��܂���\n";
	}

	if( m_bPostPixelShaderBlending == false )
	{
		strMessage += L"���ݎg�p���Ă���f�o�C�X�̓s�N�Z���V�F�[�_��̃u�����f�B���O�������g�p���邱�Ƃ��ł��܂���\n";
	}

	// �f�o�C�X��������e�N�X�`���̑傫����512�ȉ��̏ꍇ�͌x��:
	if( m_iMaxTextureWidth <= 512 || m_iMaxTextureHeight <= 512 )
	{
		WCHAR szTemp[256];
		StringCchPrintf( szTemp, 256, L"���ݎg�p���Ă���f�o�C�X�͕�%d�s�N�Z���ȉ��A����%d�s�N�Z���ȉ��̃e�N�X�`�������������Ƃ��ł��܂���\n",
					m_iMaxTextureWidth, m_iMaxTextureHeight );
		strMessage += szTemp;
	}

	if( m_bPrimBlendOp == false )
	{
		strMessage += L"���ݎg�p���Ă���f�o�C�X�́u�A���t�@���Z�v�ȊO�̃u�����f�B���O�������T�|�[�g���Ă��܂���\n";
	}

	if( strMessage.empty() )	// ���ׂĂ𖞂����Ă���ꍇ
	{
		strMessage = L"���ݎg�p���Ă���f�o�C�X�͂��ׂĂ̗v���𖞂����Ă��܂�";
	}

	MessageBox( m_hWnd, strMessage.c_str(), L"�f�o�C�X�\�͂̔���", MB_OK | MB_ICONINFORMATION );
}


void CD3DObject::ResetViewProjMatrix()
{
	_ASSERTE(m_fDisplayWidth * m_fDisplayHeight != 0.0f);

	D3DXMATRIXA16 matTemp;

	// �ˉe�s���ݒ肷��:
#ifdef PERSPECTIVE_FOV
	D3DXMatrixPerspectiveFovLH( &matTemp, m_fFov, m_fDisplayWidth / m_fDisplayHeight, m_fZNear, m_fZFar );
#else
	D3DXMatrixPerspectiveLH( &matTemp, m_fDisplayWidth, m_fDisplayHeight, m_fZNear, m_fZFar );
#endif
	m_pD3dDevice->SetTransform( D3DTS_PROJECTION, &matTemp );

	// �r���[�s���ݒ肷��:
	D3DXMatrixLookAtLH( &matTemp, &m_fEyeVec, &m_fLookAt, &m_fUpVec );
	m_pD3dDevice->SetTransform( D3DTS_VIEW, &matTemp );
}


void CD3DObject::UpdateDeviceStatsString()
{
	m_szDeviceStats[0] = L'\0';

	_ASSERTE(m_pD3dDevice != NULL);

	if( m_D3dDevType == D3DDEVTYPE_REF )
	{
		StringCchCopy( m_szDeviceStats, dwStatsStringLength, L"REF���[�h(�\�t�g�E�F�A�V�~�����[�V����)" );
	}
	else
	{
		StringCchCopy( m_szDeviceStats, dwStatsStringLength, L"HAL���[�h(�n�[�h�E�F�A�A�N�Z�����[�V����)" );
	}

	if( (m_dwCreateVertexProcessingFlag == D3DCREATE_HARDWARE_VERTEXPROCESSING) != 0 )
	{
		StringCchCat( m_szDeviceStats, dwStatsStringLength, L" - �n�[�h�E�F�A���_����" );
	}
	else if( (m_dwCreateVertexProcessingFlag & D3DCREATE_MIXED_VERTEXPROCESSING) != 0 )
	{
		StringCchCat( m_szDeviceStats, dwStatsStringLength, L" - H/S�~�b�N�X���_����" );
	}
	else if( (m_dwCreateVertexProcessingFlag & D3DCREATE_SOFTWARE_VERTEXPROCESSING) != 0 )
	{
		StringCchCat( m_szDeviceStats, dwStatsStringLength, L" - �\�t�g�E�F�A���_����" );
	}

	if( m_bCreatePureDevice )
	{
		StringCchCat( m_szDeviceStats, dwStatsStringLength, L"[PureDevice]" );
	}


	D3DADAPTER_IDENTIFIER9 adapterIdentifier;
	if( SUCCEEDED(m_pD3D->GetAdapterIdentifier( D3DADAPTER_DEFAULT, 0, &adapterIdentifier )) )
	{
		StringCchCat( m_szDeviceStats, dwStatsStringLength, L"\n�r�f�I�`�b�v: " );

		// �}���`�o�C�g���������C�h�����ɕϊ�����:
		const int iDescLength = sizeof(adapterIdentifier.Description) / sizeof(adapterIdentifier.Description[0]);
		WCHAR szDescription[iDescLength];

		MultiByteToWideChar( CP_ACP, 0, adapterIdentifier.Description, -1, szDescription, iDescLength );

		szDescription[iDescLength - 1] = L'\0';
		
		StringCchCat( m_szDeviceStats, dwStatsStringLength, szDescription );
	}

	StringCchCat( m_szDeviceStats, dwStatsStringLength, L"\n�o�b�N�o�b�t�@ �t�H�[�}�b�g: " );

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

	StringCchCat( m_szDeviceStats, dwStatsStringLength, L"\n�e�N�X�`�� �t�H�[�}�b�g: " );
	if( m_D3dFormatTexture == D3DFMT_A8R8G8B8 )
	{
		StringCchCat( m_szDeviceStats, dwStatsStringLength, L"A8R8G8B8" );
	}
	else if( m_D3dFormatTexture == D3DFMT_A4R4G4B4 )
	{
		StringCchCat( m_szDeviceStats, dwStatsStringLength, L"A4R4G4B4" );
	}

	// FPS�\���̈ʒu��ݒ肷��:
	size_t stLength = 0;
	StringCchLength( m_szDeviceStats, dwStatsStringLength, &stLength );
	m_lpszFpsStats = m_szDeviceStats + stLength;
}


void CD3DObject::UpdateFpsStatsString()
{
	static int iCount = 0;	// 1�b�Ԃɕ`�悳�ꂽ��
	static DWORD dwLastTime = 0;	// �Ō�ɍX�V��������
	
	const DWORD dwNowTime = GetTickCount();

	// 1�b�ԂōX�V����
	if( dwNowTime - dwLastTime >= 1000 )
	{
		const DWORD dwLastLength = dwStatsStringLength - (DWORD)(m_lpszFpsStats - m_szDeviceStats);
		_ASSERTE(IsBadWritePtr( m_lpszFpsStats, dwLastLength ) == FALSE);

		const FLOAT fFramePerSec = (FLOAT)(iCount * 1000) / (dwNowTime - dwLastTime);

		StringCchPrintf( m_lpszFpsStats, dwLastLength, L"\n%.1f �t���[�� / �b", fFramePerSec );

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
	if( m_bDeviceInitialized == false ) { return; }	// �܂�����������Ă��Ȃ��ꍇ

	HRESULT hr = S_OK;

	// �J�����O�𖳌��ɂ���
//	VALID(m_pD3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE));

    // ���C�e�B���O��L���ɂ���
    VALID(m_pD3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE));
	VALID(m_pD3dDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020));

	// �V�F�[�f�B���O���@��ݒ肷��
	VALID(m_pD3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD));

	// �N���b�s���O�𖳌��ɂ���
	VALID(m_pD3dDevice->SetRenderState(D3DRS_CLIPPING, FALSE));

	// �[�x�o�b�t�@�𗘗p���Ȃ��ꍇ��Z�o�b�t�@�𖳌��ɂ���
	if( m_bEnableStencilMask == false ) { VALID(m_pD3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE)); }

	// �e�N�X�`���̃A���t�@�֘A�̐ݒ� : �`��F��A�l���s�����x�ɂȂ�悤�ɐݒ�:
	VALID(m_pD3dDevice->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_MODULATE));
	VALID(m_pD3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE));
	VALID(m_pD3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE));
	VALID(m_pD3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE));
	VALID(m_pD3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE));
	VALID(m_pD3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE));
	VALID(m_pD3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE));
	VALID(m_pD3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA ));
	VALID(m_pD3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA));
	
	// �e�N�X�`���T���v�����O���[�h��ݒ�:
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
	OnLostDevice();	// �f�o�C�X�������������̏���

	HRESULT hr = m_pD3dDevice->Reset( &m_D3dPresentParam );
	while( FAILED(hr) )
	{
		// TestCooperativeLevel()��D3DERR_DEVICENOTRESET��Ԃ��܂őҋ@:
		hr = m_pD3dDevice->TestCooperativeLevel();
		switch( hr )
		{
		case D3DERR_DEVICELOST:

			Sleep(100);	// �f�o�C�X�����������̂őҋ@����
			break;

		case D3DERR_DEVICENOTRESET:

			m_bDeviceLost = true;	// �f�o�C�X���������
		// �K�v�Ȃ���������Ȃ�	OnLostDevice();	// �f�o�C�X�������������̏���

			hr = m_pD3dDevice->Reset( &m_D3dPresentParam );
			if( FAILED(hr) )	// ���Z�b�g�ł��Ȃ������ꍇ
			{
				MessageBox( m_hWnd, L"�f�o�C�X�̃��Z�b�g�Ɏ��s���܂���", L"�f�o�C�X�̏���", MB_OK | MB_ICONERROR );
				VALID_RETURN(hr);
			}
			break;
		}	//-----switch( m_pd3dDevice->TestCooperativeLevel() )-----
	}	//-----while( FAILED(hr) )-----

	OnResetDevice();	// �f�o�C�X�����Z�b�g�������̏���

	InitDeviceStats();	// �f�o�C�X�̏�Ԃ�ݒ肷��

	ResetTimer();	// �^�C�}�[�����Z�b�g����

	UpdateDeviceStatsString();	// �f�o�C�X�̏����X�V����

	ResetViewProjMatrix();	// �r���[�s��ƁA�ˉe�s������Z�b�g����

	m_bDeviceLost = false;	// �f�o�C�X������Ԃ�ݒ肷��

	return true;
}



bool CD3DObject::Initialize(HWND hWnd)
{
	if( m_pD3D == NULL )	// D3D�I�u�W�F�N�g���܂��쐬����Ă��Ȃ��ꍇ
	{
		// D3DX�̃o�[�W�������m�F����
		if( D3DXCheckVersion( D3D_SDK_VERSION, D3DX_SDK_VERSION ) == FALSE )
		{
			MessageBox( m_hWnd, L"DirectX�̃o�[�W�������Ⴂ�܂��B�V����DirectX���C���X�g�[�����Ă�������",
				L"DirectX�̃o�[�W�����m�F", MB_OK | MB_ICONERROR );
			return false;
		}

		// Direct3D�I�u�W�F�N�g���쐬����
		m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
		if( m_pD3D == NULL )
		{
			MessageBox( m_hWnd, L"Direct3D�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���",
				L"Direct3D�I�u�W�F�N�g�̍쐬", MB_OK | MB_ICONERROR );
			return false;
		}
	}

	if( m_bDeviceInitialized == false )	// �܂�����������Ă��Ȃ��ꍇ
	{
		_ASSERTE(m_hWnd == NULL);
		m_hWnd = hWnd;	// �E�B���h�E��ݒ肷��

		_ASSERTE(m_pD3dDevice == NULL);

		InitSettings();	// �ݒ������������

		// Direct3D�f�o�C�X���쐬����
		if( CreateDevice() == false )	// ���s�����ꍇ
		{
			InitSettings();	// �ݒ������������
			m_bCreatePureDevice = false;	// D3DCREATE_PUREDEVICE��OFF�ɂ��č쐬����

			if( CreateDevice() == false )	// ����Ɏ��s�����ꍇ
			{
				InitSettings();	// �ݒ������������
				m_bCreatePureDevice = false;	// D3DCREATE_PUREDEVICE��OFF�ɂ��č쐬����
				m_D3dDevType = D3DDEVTYPE_REF;	// REF���[�h�Ńf�o�C�X���쐬����

				if( CreateDevice() == false )	// ����ł����s�����ꍇ
				{
					MessageBox( m_hWnd, L"Direct3D�f�o�C�X�̍쐬�Ɏ��s���܂���",
						L"Direct3D�f�o�C�X�̍쐬", MB_OK | MB_ICONERROR );
					return false;
				}
			}
		}

		if( m_D3dDevType == D3DDEVTYPE_REF )	// REF���[�h�ō쐬�����ꍇ�̓��b�Z�[�W��\������
		{
			MessageBox( m_hWnd, L"Direct3D�f�o�C�X��REF���[�h�ō쐬���܂����B����͔��ɒx���Ȃ�܂�",
				L"Direct3D�f�o�C�X�̍쐬", MB_OK | MB_ICONWARNING );
		}

		if( CreateFont() == false ) { return false; }	// �t�H���g���쐬����
		//������ if( LoadEffectFile() == false ) { return false; }	// �G�t�F�N�g�t�@�C����ǂݍ���

		AdjustDisplayToBackBuffer();	// �f�B�X�v���C�̈�̃f�t�H���g�̓o�b�N�o�b�t�@�̗̈�ɂ���

		m_bDeviceInitialized = true;
	}

	_ASSERTE(m_pD3dDevice != NULL);
	_ASSERTE(m_hWnd == hWnd);	// �ŏ��ɏ������������ƈႤ�E�B���h�E���w�肳�ꂽ

	const bool bReset = Reset3DEnvironment();	// 3D�������Z�b�g����
	_ASSERTE(bReset == true);

	return bReset;
}


void CD3DObject::SetDisplayWidthHeight(const FLOAT fWidth, const FLOAT fHeight)
{
	if( fWidth * fHeight == 0.0f ) { return; }

	m_fDisplayWidth = fWidth;
	m_fDisplayHeight = fHeight;

	ResetViewProjMatrix();	// �r���[�s��Ǝˉe�s����X�V����
}


void CD3DObject::AdjustDisplayToBackBuffer()
{
	_ASSERTE(m_D3dPresentParam.BackBufferWidth * m_D3dPresentParam.BackBufferHeight > 0);

	m_fDisplayWidth = (FLOAT)m_D3dPresentParam.BackBufferWidth;
	m_fDisplayHeight = (FLOAT)m_D3dPresentParam.BackBufferHeight;

	ResetViewProjMatrix();	// �r���[�s��Ǝˉe�s����X�V����
}


bool CD3DObject::LoadBackGroundTexture(LPCWSTR lpszFileName)
{
	_ASSERTE(m_pD3dDevice != NULL);
	_ASSERTE(IsBadStringPtr( lpszFileName, MAX_PATH ) == FALSE);

	if( PathFileExists( lpszFileName ) == FALSE ) { return false; }

	SAFE_RELEASE(m_pD3dTextureBG);	// ������Ă���

	HRESULT hr = S_OK;

	D3DXIMAGE_INFO d3DImageInfo;
	VALID_RETURN(D3DXCreateTextureFromFileEx( m_pD3dDevice, lpszFileName, D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_UNKNOWN, 
											D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, &d3DImageInfo, NULL, &m_pD3dTextureBG ));

	D3DSURFACE_DESC d3DSurfaceDesc;
	VALID_RETURN(m_pD3dTextureBG->GetLevelDesc( 0, &d3DSurfaceDesc ));

	// U,V���W���v�Z����:
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

	// �T�C�Y���Ⴄ�ꍇ�̓o�b�N�o�b�t�@�̃T�C�Y��ύX���ă��Z�b�g����
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

	// ������
    
	SetRenderingPause( false );
}



void CD3DObject::RenderScene()
{
	_ASSERTE(m_bDeviceInitialized == true);
	_ASSERTE(m_hWnd != NULL);

	HRESULT hr = S_OK;

	if( m_bRenderingPaused ) { Sleep( 100 ); }	// ��~��Ԃ̎���CPU�����̏������ł���悤�ɂ���
	if( m_bDeviceLost ) { return; }	// �f�o�C�X��������Ԃ̎��͕`�悵�Ȃ�


	const DWORD dwClearFlag = D3DCLEAR_TARGET | (m_bEnableStencilMask ? D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL : 0);

	VALID(m_pD3dDevice->Clear(0, NULL, dwClearFlag, m_dwBgColor, 1.0f, 0));

	if( SUCCEEDED(m_pD3dDevice->BeginScene()) )
	{
		// ���[���h�s�������������:
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity( &matWorld );
		m_pD3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

		if( m_bShowBackGround )	// �w�i��\������ꍇ
		{
			DrawBackGround();
		}

		if( m_pD3dModel != NULL )	// ���f���f�[�^���ǂݍ��܂�Ă���ꍇ
		{
			m_pD3dModel->Show( m_pD3dDevice );	// ���f���f�[�^��\������
		}

		if( m_bShowDeviceStats )	// �f�o�C�X����\������ꍇ
		{
			UpdateFpsStatsString();	// FPS���X�V����
			DrawDeviceStatsString();
		}

		m_pD3dDevice->EndScene();

		hr = m_pD3dDevice->Present( NULL, NULL, NULL, NULL );
		if( FAILED(hr ) )
		{
			if( hr == D3DERR_DEVICELOST ) { m_bDeviceLost = true; }	// �f�o�C�X���������

			VALID(hr);	// �f�o�b�O���ɃG���[���b�Z�[�W��\������

			Reset3DEnvironment();	// �`��������Z�b�g����
		}
	}
}



bool CD3DObject::LoadModel(ColladaObject* pColladaObj)
{
	_ASSERTE(m_pD3dDevice != NULL);
	_ASSERTE(pColladaObj != NULL);

	SAFE_DELETE(m_pD3dModel);	// ������Ă���

	m_pD3dModel = new D3DModel();

	if( m_pD3dModel->Read( m_pD3dDevice, pColladaObj ) == false )
	{
		std::wstring strMessage = L"���f���f�[�^���쐬���ɃG���[���������܂���";
		MessageBox( NULL, strMessage.c_str(), L"CD3DObject::LoadModel", MB_OK | MB_ICONERROR );
		return false;
	}

	return true;
}

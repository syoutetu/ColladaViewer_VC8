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

	LPD3DXFONT	m_pD3dFont;	// �e�L�X�g����\������t�H���g�I�u�W�F�N�g
	
	static const DWORD	dwStatsStringLength = 1024;	// �e�L�X�g���̕�����̒���
	WCHAR	m_szDeviceStats[dwStatsStringLength];	// �f�o�C�X��Ԃ�\�����镶����
	WCHAR	m_szMovieInfo[dwStatsStringLength];		// ���[�r�[����\�����镶����
	
	LPTSTR	m_lpszFpsStats;	// FPS����\�����镶����̈ʒu(m_szDeviceStats�̈ꕔ���g�p����)

	DWORD	m_dwBgColor;	// �w�i�F

	LPDIRECT3DTEXTURE9	m_pD3dTextureBG;	// �w�i�Ɏg�p����e�N�X�`��
	FLOAT	m_fBgTextureU;	// �w�i�Ɏg�p����e�N�X�`��U���W�̕�
	FLOAT	m_fBgTextureV;	// �w�i�Ɏg�p����e�N�X�`��V���W�̍���

	FLOAT	m_fDisplayWidth;	// �\������̈�̕�
	FLOAT	m_fDisplayHeight;	// �\������̈�̍���

	HWND	m_hWnd;		// �^�[�Q�b�g�E�B���h�E
	bool	m_bFullScreen;			// �t���X�N���[���\��
	bool	m_bDeviceInitialized;	// �f�o�C�X�����������ꂽ
	bool	m_bRenderingPaused;		// �����_�����O����~���ꂽ
	bool	m_bDeviceLost;			// �f�o�C�X���������

	bool	m_bShowDeviceStats;		// �f�o�C�X��Ԃ̃e�L�X�g��\������
	bool	m_bShowBackGround;		// �w�i��\������


	// �v������f�o�C�X�̐ݒ�(�f�o�C�X�̔\�͂��s�������ꍇ�͕ύX�����):
	D3DPRESENT_PARAMETERS	m_D3dPresentParam;
	D3DDEVTYPE	m_D3dDevType;
	bool	m_bCreatePureDevice;			// CreateDevice�Őݒ肷��PUREDEVICE�̃t���O
	DWORD	m_dwCreateVertexProcessingFlag;	// CreateDevice�Őݒ肷��VERTEXPROCESSING�̃t���O
	
	bool	m_bEnablePixelShader;	// �s�N�Z���V�F�[�_���g�p�ł���
	ShaderVersion	m_PSVersion;	// �s�N�Z���V�F�[�_�̃o�[�W����
	bool	m_bEnableVertexShader;	// ���_�V�F�[�_���g�p�ł���
	ShaderVersion	m_VSVersion;	// ���_�V�F�[�_�̃o�[�W����
	
	bool	m_bEnableStencilMask;	// �[�x�o�b�t�@���g�p�ł���
	D3DFORMAT	m_D3dFormatDepth;	// �[�x�o�b�t�@�̃t�H�[�}�b�g

	D3DFORMAT	m_D3dFormatAdapter;	// �A�_�v�^�f�B�X�v���C�̃t�H�[�}�b�g
	D3DFORMAT	m_D3dFormatTexture;	// �e�N�X�`���̃t�H�[�}�b�g

	bool	m_bPrimBlendOp;				// D3DBLENDOP_ADD �ȊO�̃A���t�@�u�����f�B���O�������T�|�[�g����
	bool	m_bPostPixelShaderBlending;	// �s�N�Z���V�F�[�_��̃A���t�@�u�����f�B���O���T�|�[�g����
	int		m_iMaxTextureWidth;			// �g�p�ł���ő�̃e�N�X�`���̕�
	int		m_iMaxTextureHeight;		// �g�p�ł���ő�̃e�N�X�`���̍���


	LPD3DXEFFECT	m_pD3dEffect;	// �G�t�F�N�g�I�u�W�F�N�g
	D3DModel*		m_pD3dModel;	// ���f���I�u�W�F�N�g


	void InitSettings();	// �v�����鏉���ݒ���s��

	bool CreateFont();	// �t�H���g���쐬����
	bool LoadEffectFile();	// �G�t�F�N�g�t�@�C����ǂݍ���

	void CleanupD3dDevice();	// D3DDevice���������

	void ResetPresentParam();	// D3DPRESENT_PARAMETERS�\���̂�ݒ肷��

	bool CreateDevice();	// �f�o�C�X���쐬����

	bool ValidateDeviceBeforeCreate();	// �f�o�C�X�̍쐬�O�ɐݒ���m�F���鏈��

	void DrawBackGround() const;	// �w�i��`�悷��

	void DrawDeviceStatsString() const;	// �f�o�C�X��Ԃ̃e�L�X�g��`�悷��
	void DrawMovieInfoString() const;	// ���[�r�[���̃e�L�X�g��`�悷��

	void ShowDeviceValidationMessage() const;	// �f�o�C�X�̔\�͂Ɋւ���񍐂�\������

	void ResetViewProjMatrix();	// �r���[�s��Ǝˉe�s������Z�b�g����

	void UpdateDeviceStatsString();	// �f�o�C�X�̏����X�V����
	void UpdateFpsStatsString();	// �t���[�����[�g�̏����X�V����

	void InitDeviceStats();	// �f�o�C�X���Đݒ肷�鎞�̏���

	void OnResetDevice();	// �f�o�C�X�����Z�b�g���ꂽ���̏���
	void OnLostDevice();	// �f�o�C�X�������������̏���

	bool Reset3DEnvironment();	// 3D�������Z�b�g����

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

	bool Initialize(HWND hWnd);	// �f�o�C�X������������

	FLOAT GetDisplayWidth() const	{ return m_fDisplayWidth; }
	FLOAT GetDisplayHeight() const	{ return m_fDisplayHeight; }

	void SetDisplayWidthHeight(const FLOAT fWidth, const FLOAT fHeight);	// �f�B�X�v���C�̗̈��ݒ肷��
	void AdjustDisplayToBackBuffer();	// �f�B�X�v���C�̗̈���o�b�N�o�b�t�@�̗̈�ɂ��킹��

	void SetBackGroundColor(const DWORD dwColor)	{ m_dwBgColor = dwColor; }	// �w�i�F��ݒ肷��

	bool LoadBackGroundTexture(LPCWSTR lpszFileName);	// �w�i�Ɏg�p����摜��ǂݍ���

	void ResetTimer()	{ m_dwLastTime = GetTickCount(); }	// �o�ߎ��Ԃ��擾����^�C�}�[�����Z�b�g���� 
	DWORD GetElapsedTime() const	{ return GetTickCount() - m_dwLastTime; }	// ���Z�b�g����������̌o�ߎ��Ԃ��擾����(�P��:�~���Z�J���h)

	void AdjustBackBufferToClient();	// �o�b�N�o�b�t�@�͈̔͂��E�B���h�E�̃N���C�A���g�͈͂ɂ��킹��

	void ToggleFullScreen();	// �t���X�N���[���؂�ւ�

	void RenderScene();	// �`�悷��

	bool LoadModel(ColladaObject* pColladaObj);
};



CD3DObject& GetD3DObject();	// �O���[�o���ȐÓI�I�u�W�F�N�g���擾����


#endif	//___D3DObject_h___

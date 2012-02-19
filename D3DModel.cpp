#include "stdafx.h"

#include "D3DCommon.h"
#include "D3DModel.h"




D3DModel::D3DModel()
{
}


D3DModel::~D3DModel()
{
	for( VECD3DXMESH::iterator it = vecD3dMesh.begin(); it != vecD3dMesh.end(); ++it )
	{
		SAFE_RELEASE(*it);
	}
	vecD3dMesh.clear();
}



bool D3DModel::Read(IDirect3DDevice9* d3dDevice, ColladaObject* colladaObj)
{
	_ASSERTE(d3dDevice != NULL);
	_ASSERTE(colladaObj != NULL);

	VECGEOMETRYELEM vecGeometry;
	colladaObj->GetGeometryElement( vecGeometry );
	_ASSERTE(vecGeometry.empty() == false);

	for( VECGEOMETRYELEM::const_iterator it = vecGeometry.begin(); it != vecGeometry.end(); ++it )
	{
		MeshElement* elemMesh = (*it)->GetMeshElement();
		if( elemMesh == NULL ) { return false; }

		if( ReadMeshElement( d3dDevice, elemMesh ) == false ) { return false; }
	}

	return true;
}


void D3DModel::Show(IDirect3DDevice9* d3dDevice)
{
	_ASSERTE(d3dDevice != NULL);


	HRESULT hr = S_OK;


	// �܂��}�e���A���⃉�C�g�̃p�����[�^���擾�ł��Ȃ��̂�
	// �K���ȃp�����[�^�ŌŒ肵�Ă���:
	D3DMATERIAL9 mtrl;
    ZeroMemory( &mtrl, sizeof(D3DMATERIAL9) );
    mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
    mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
    mtrl.Diffuse.b = mtrl.Ambient.b = 0.0f;
    mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	d3dDevice->SetMaterial( &mtrl );

    D3DXVECTOR3 vecDir;
    D3DLIGHT9 light;
    ZeroMemory( &light, sizeof(D3DLIGHT9) );
    light.Type       = D3DLIGHT_DIRECTIONAL;
    light.Diffuse.r  = 1.0f;
    light.Diffuse.g  = 1.0f;
    light.Diffuse.b  = 1.0f;
	vecDir = D3DXVECTOR3( -1.0f, -1.0f, 1.0f );
    D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );
    light.Range       = 1000.0f;
    d3dDevice->SetLight( 0, &light );
    d3dDevice->LightEnable( 0, TRUE );

	// �K���ȉ�]:
	static float degree = 0.0f;
	degree += 1.0f;
	D3DXMATRIXA16 matWorld;
	D3DXMatrixRotationY( &matWorld, degree / 180.0f );
	d3dDevice->SetTransform( D3DTS_WORLD, &matWorld );


	for( VECD3DXMESH::const_iterator it = vecD3dMesh.begin(); it != vecD3dMesh.end(); ++it )
	{
		VALID((*it)->DrawSubset( 0 ));
	}
}




bool D3DModel::ReadMeshElement(IDirect3DDevice9* d3dDevice, MeshElement* elemMesh)
{
	_ASSERTE(d3dDevice != NULL);
	_ASSERTE(elemMesh != NULL);

	HRESULT hr = S_OK;

	if( elemMesh->GetPolygonsCount() == 0 ) { return false; }		// �Ƃ肠����polygons�Ɍ��肵�đΉ�
	PolygonsElement* elemPolgon = elemMesh->GetPolygonsElement( 0 );

	// Input�G�������g����D3D���b�V���̒��_�錾��ݒ肷��:
	D3DVERTEXELEMENT9 declVertex[8];	// �K���ȑ傫�����m�ۂ���
	ZeroMemory( declVertex, sizeof(declVertex) );
	WORD offset = 0;		// ���̃f�[�^�̃I�t�Z�b�g
	DWORD index = 0;		// �z��̃C���f�b�N�X

	VECINPUTELEM vecInput;
	elemMesh->GetAllInputElement( elemPolgon, vecInput, true );	// ���ׂĂ�input�v�f���擾����
	for( VECINPUTELEM::iterator it = vecInput.begin(); it != vecInput.end(); ++it )
	{
		if( (*it)->IsPositionSemantic() )
		{
			D3DVERTEXELEMENT9 d3dVert = DECL_VERTEXELEM_POSITION(offset);
			declVertex[index++] = d3dVert;
			offset += 3 * sizeof(float);
		}
		else if( (*it)->IsNormalSemantic() )
		{
			D3DVERTEXELEMENT9 d3dVert = DECL_VERTEXELEM_NORMAL(offset);
			declVertex[index++] = d3dVert;
			offset += 3 * sizeof(float);
		}
		else if( (*it)->IsTexCoordSemantic() )
		{
			D3DVERTEXELEMENT9 d3dVert = DECL_VERTEXELEM_TEXCOORD(offset);
			declVertex[index++] = d3dVert;
			offset += 2 * sizeof(float);
		}
		else { _ASSERTE(!"UnknownSemanticType"); }
	}

	D3DVERTEXELEMENT9 d3dVertEnd = D3DDECL_END();
	declVertex[index] = d3dVertEnd;	// �Ō�ɕK�v

	// ���b�V���f�[�^���g���C�A���O�����X�g�Ŏ擾����:
	unsigned int vertexCount;
	float* vertexData;
	if( elemMesh->CreateTriangleList( vertexCount, vertexData ) == false ) { return false; }

	// D3D���b�V�����쐬����(�C���f�b�N�X��32bit�Ȃ̂�D3DXMESH_32BIT���K�v):
	ID3DXMesh* d3dMesh = NULL;
	DWORD usage = D3DXMESH_MANAGED | D3DXMESH_32BIT | D3DXMESH_DONOTCLIP;
	VALID_RETURN(D3DXCreateMesh( vertexCount / 3, vertexCount, usage, declVertex, d3dDevice, &d3dMesh ));
	vecD3dMesh.push_back( d3dMesh );
    
	// ���_�f�[�^���R�s�[����:
	float* pLockVertex;
	VALID(d3dMesh->LockVertexBuffer( 0, (void**)&pLockVertex ));
	memcpy( pLockVertex, vertexData, vertexCount * offset );
	VALID(d3dMesh->UnlockVertexBuffer());
	SAFE_DELETE_ARRAY(vertexData);
	pLockVertex = NULL;

	// �Ƃ肠�����C���f�b�N�X�͂��̂܂܂̏��Ԃɐݒ肷��:
	unsigned int* pLockIndex;
	VALID(d3dMesh->LockIndexBuffer( 0, (void**)&pLockIndex ));
	for( unsigned int i = 0; i < vertexCount; i++ ) { *(pLockIndex++) = i; }
	VALID(d3dMesh->UnlockIndexBuffer());
	pLockIndex = NULL;

	return true;
}


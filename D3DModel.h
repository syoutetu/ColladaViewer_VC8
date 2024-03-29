
#pragma once

#if !defined ___D3DModel_h___
#define ___D3DModel_h___


#include "ColladaObject.h"


typedef std::vector<ID3DXMesh*> VECD3DXMESH;


class D3DModel
{

public:

	D3DModel();
	~D3DModel();


	bool Read(IDirect3DDevice9* d3dDevice, ColladaObject* colladaObject);			// ColladaObjectを読み込む


	void Show(IDirect3DDevice9* d3dDevice);


private:

	VECD3DXMESH		vecD3dMesh;
	
	bool ReadMeshElement(IDirect3DDevice9* d3dDevice, MeshElement* elemMesh);		// MeshElementを読み込む

};


#endif	//___D3DModel_h___
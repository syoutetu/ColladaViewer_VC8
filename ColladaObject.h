
#pragma once

#if !defined ___ColladaObject_h___
#define ___ColladaObject_h___


#include "ColladaElement.h"
#include "LibraryElement.h"
#include "AssetElement.h"
#include "SceneElement.h"
#include "AnimationLibrary.h"
#include "CameraLibrary.h"
#include "CodeLibrary.h"
#include "ControllerLibrary.h"
#include "GeometryLibrary.h"
#include "ImageLibrary.h"
#include "LightLibrary.h"
#include "MaterialLibrary.h"
#include "ProgramLibrary.h"
#include "TextureLibrary.h"



class ColladaObject
{

public:

	ColladaObject();
	~ColladaObject();

	void Clear();

	void ReadRootNode(const DOMNode* node);

	bool ValidElements();

	const std::wstring& GetErrorMessage() const	{ return strErrorMessage; }

	void GetAnimationElement(VECANIMATIONELEM& vecAnimation) const;
	void GetCameraElement(VECCAMERAELEM& vecCamera) const;
	void GetCodeElement(VECCODEELEM& vecCode) const;
	void GetControllerElement(VECCONTROLLERELEM& vecController) const;
	void GetGeometryElement(VECGEOMETRYELEM& vecGeometry) const;
	void GetImageElement(VECIMAGEELEM& vecImage) const;
	void GetLightElement(VECLIGHTELEM& vecLight) const;
	void GetMaterialElement(VECMATERIALELEM& vecMaterial) const;
	void GetProgramElement(VECPROGRAMELEM& vecProgram) const;
	void GetTextureElement(VECTEXTUREELEM& vecTexture) const;

private:

	//========================================================
	// �G�������g
	//========================================================
	ColladaElement*	elemCollada;		// �K��1���݂���
	AssetElement*	elemAsset;			// �K��1���݂���

	VECLIBRARYELEM	vecElemLibrary;		// 0�ȏ㑶�݂���
	SceneElement*	elemScene;			// 0�܂���1���݂���


	std::wstring	strErrorMessage;


	static LibraryElement* CreateLibraryElement(const DOMNode* node);	// Library�v�f���쐬����

	void GetLibrary(VECLIBRARYELEM& vecLibrary, LibraryElement::TYPE type) const;
};



#endif	//___ColladaObject_h___
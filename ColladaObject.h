
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
	// エレメント
	//========================================================
	ColladaElement*	elemCollada;		// 必ず1つ存在する
	AssetElement*	elemAsset;			// 必ず1つ存在する

	VECLIBRARYELEM	vecElemLibrary;		// 0以上存在する
	SceneElement*	elemScene;			// 0または1つ存在する


	std::wstring	strErrorMessage;


	static LibraryElement* CreateLibraryElement(const DOMNode* node);	// Library要素を作成する

	void GetLibrary(VECLIBRARYELEM& vecLibrary, LibraryElement::TYPE type) const;
};



#endif	//___ColladaObject_h___
#include "stdafx.h"

#include "ColladaObject.h"



ColladaObject::ColladaObject()
{
	elemCollada = new ColladaElement();
	elemAsset = NULL;
	elemScene = NULL;
}


ColladaObject::~ColladaObject()
{
	Clear();
}


void ColladaObject::Clear()
{
	SAFE_DELETE(elemCollada);
	SAFE_DELETE(elemAsset);
	SAFE_DELETE(elemScene);

	ClearVector( vecElemLibrary );
}



void ColladaObject::ReadRootNode(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNode* currentNode = node->getFirstChild();
	while( currentNode != NULL )
	{
#if _DEBUG	// デバッグ時に名前をチェックする為に
		const XMLCh* name = currentNode->getNodeName();
#endif
		if( IsElementNode( currentNode ) )
		{
			if( Is_COLLADA_NodeName( currentNode ) )		// COLLADA要素が見つかった場合
			{
				currentNode = currentNode->getFirstChild();		// 子ノードを処理する
				continue;
			}
			else if( Is_asset_NodeName( currentNode ) )	// asset要素が見つかった場合
			{
				_ASSERTE(elemAsset == NULL);		// 必ず1つ存在するのでこの時点ではNULL

				elemAsset = new AssetElement();
				elemAsset->ReadNode( currentNode );
			}
			else if( Is_library_NodeName( currentNode ) )	// library要素が見つかった場合
			{
				LibraryElement* elemLibrary = CreateLibraryElement( currentNode );
				if( elemLibrary != NULL )
				{
					elemLibrary->ReadNode( currentNode );
					vecElemLibrary.push_back( elemLibrary );
				}
			}
			else if( Is_scene_NodeName( currentNode ) )	// scene要素が見つかった場合
			{
				_ASSERTE(elemScene == NULL);		// 0または1つ存在するのでこの時点ではNULL

				elemScene = new SceneElement();
				elemScene->ReadNode( currentNode );
			}
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}



// 必要な要素が読み込まれている場合はtrueを返す
// 要素が不完全な場合はエラーメッセージを設定してfalseを返す
bool ColladaObject::ValidElements()
{
	strErrorMessage.clear();		// メッセージを消去する

	if( elemCollada == NULL ) { strErrorMessage += L"・<COLLADA>要素が見つかりませんでした\n"; }	// 必ず存在する

	if( elemAsset != NULL )
	{
		elemAsset->ValidElements( strErrorMessage );
	}
	else	// 必ず存在する
	{
		strErrorMessage += L"・<asset>要素が見つかりませんでした\n";
	}

	ValidElementsInContainer( vecElemLibrary, strErrorMessage );

	if( elemScene != NULL )
	{
		elemScene->ValidElements( strErrorMessage );
	}

	return strErrorMessage.empty();		// エラーがない場合はtrueを返す
}




void ColladaObject::GetAnimationElement(VECANIMATIONELEM& vecAnimation) const
{
	VECLIBRARYELEM vecLib;
	GetLibrary( vecLib, LibraryElement::TYPE_ANIMATION );

	for( VECLIBRARYELEM::const_iterator it = vecLib.begin(); it != vecLib.end(); ++it )
	{
		for( unsigned int i = 0; i < (*it)->GetCount(); i++ )
		{
			vecAnimation.push_back( (AnimationElement*)(*it)->GetElement( i ) );
		}
	}
}


void ColladaObject::GetCameraElement(VECCAMERAELEM& vecCamera) const
{
	VECLIBRARYELEM vecLib;
	GetLibrary( vecLib, LibraryElement::TYPE_CAMERA );

	for( VECLIBRARYELEM::const_iterator it = vecLib.begin(); it != vecLib.end(); ++it )
	{
		for( unsigned int i = 0;  i < (*it)->GetCount(); i++ )
		{
			vecCamera.push_back( (CameraElement*)(*it)->GetElement( i ) );
		}
	}
}


void ColladaObject::GetCodeElement(VECCODEELEM& vecCode) const
{
	VECLIBRARYELEM vecLib;
	GetLibrary( vecLib, LibraryElement::TYPE_CODE );

	for( VECLIBRARYELEM::const_iterator it = vecLib.begin(); it != vecLib.end(); ++it )
	{
		for( unsigned int i = 0;  i < (*it)->GetCount(); i++ )
		{
			vecCode.push_back( (CodeElement*)(*it)->GetElement( i ) );
		}
	}
}


void ColladaObject::GetControllerElement(VECCONTROLLERELEM& vecController) const
{
	VECLIBRARYELEM vecLib;
	GetLibrary( vecLib, LibraryElement::TYPE_CONTROLLER );

	for( VECLIBRARYELEM::const_iterator it = vecLib.begin(); it != vecLib.end(); ++it )
	{
		for( unsigned int i = 0;  i < (*it)->GetCount(); i++ )
		{
			vecController.push_back( (ControllerElement*)(*it)->GetElement( i ) );
		}
	}
}


void ColladaObject::GetGeometryElement(VECGEOMETRYELEM& vecGeometry) const
{
	VECLIBRARYELEM vecLib;
	GetLibrary( vecLib, LibraryElement::TYPE_GEOMETRY );

	for( VECLIBRARYELEM::const_iterator it = vecLib.begin(); it != vecLib.end(); ++it )
	{
		for( unsigned int i = 0; i < (*it)->GetCount(); i++ )
		{
			vecGeometry.push_back( (GeometryElement*)(*it)->GetElement( i ) );
		}
	}
}


void ColladaObject::GetImageElement(VECIMAGEELEM& vecImage) const
{
	VECLIBRARYELEM vecLib;
	GetLibrary( vecLib, LibraryElement::TYPE_IMAGE );

	for( VECLIBRARYELEM::const_iterator it = vecLib.begin(); it != vecLib.end(); ++it )
	{
		for( unsigned int i = 0;  i < (*it)->GetCount(); i++ )
		{
			vecImage.push_back( (ImageElement*)(*it)->GetElement( i ) );
		}
	}
}


void ColladaObject::GetLightElement(VECLIGHTELEM& vecLight) const
{
	VECLIBRARYELEM vecLib;
	GetLibrary( vecLib, LibraryElement::TYPE_LIGHT );

	for( VECLIBRARYELEM::const_iterator it = vecLib.begin(); it != vecLib.end(); ++it )
	{
		for( unsigned int i = 0;  i < (*it)->GetCount(); i++ )
		{
			vecLight.push_back( (LightElement*)(*it)->GetElement( i ) );
		}
	}
}


void ColladaObject::GetMaterialElement(VECMATERIALELEM& vecMaterial) const
{
	VECLIBRARYELEM vecLib;
	GetLibrary( vecLib, LibraryElement::TYPE_MATERIAL );

	for( VECLIBRARYELEM::const_iterator it = vecLib.begin(); it != vecLib.end(); ++it )
	{
		for( unsigned int i = 0;  i < (*it)->GetCount(); i++ )
		{
			vecMaterial.push_back( (MaterialElement*)(*it)->GetElement( i ) );
		}
	}
}


void ColladaObject::GetProgramElement(VECPROGRAMELEM& vecProgram) const
{
	VECLIBRARYELEM vecLib;
	GetLibrary( vecLib, LibraryElement::TYPE_PROGRAM );

	for( VECLIBRARYELEM::const_iterator it = vecLib.begin(); it != vecLib.end(); ++it )
	{
		for( unsigned int i = 0;  i < (*it)->GetCount(); i++ )
		{
			vecProgram.push_back( (ProgramElement*)(*it)->GetElement( i ) );
		}
	}
}


void ColladaObject::GetTextureElement(VECTEXTUREELEM& vecTexture) const
{
	VECLIBRARYELEM vecLib;
	GetLibrary( vecLib, LibraryElement::TYPE_TEXTURE );

	for( VECLIBRARYELEM::const_iterator it = vecLib.begin(); it != vecLib.end(); ++it )
	{
		for( unsigned int i = 0;  i < (*it)->GetCount(); i++ )
		{
			vecTexture.push_back( (TextureElement*)(*it)->GetElement( i ) );
		}
	}
}



LibraryElement* ColladaObject::CreateLibraryElement(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	if( IsElementNode( node ) == false ) { return NULL; }
	
	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return NULL; }

	const DOMNode* type = attr->getNamedItem( (const XMLCh*)L"type" );
	if( type == NULL ) { return NULL; }

	LibraryElement* library = NULL;

	if( IsNodeValueEquals( type, L"ANIMATION" ) )
	{
		library = new AnimationLibrary();
	}
	else if( IsNodeValueEquals( type, L"CAMERA" ) )
	{
		library = new CameraLibrary();
	}
	else if( IsNodeValueEquals( type, L"CODE" ) )
	{
		library = new CodeLibrary();
	}
	else if( IsNodeValueEquals( type, L"CONTROLLER" ) )
	{
		library = new ControllerLibrary();
	}
	else if( IsNodeValueEquals( type, L"GEOMETRY" ) )
	{
		library = new GeometryLibrary();
	}
	else if( IsNodeValueEquals( type, L"IMAGE" ) )
	{
		library = new ImageLibrary();
	}
	else if( IsNodeValueEquals( type, L"LIGHT" ) )
	{
		library = new LightLibrary();
	}
	else if( IsNodeValueEquals( type, L"MATERIAL" ) )
	{
		library = new MaterialLibrary();
	}
	else if( IsNodeValueEquals( type, L"PROGRAM" ) )
	{
		library = new ProgramLibrary();
	}
	else if( IsNodeValueEquals( type, L"TEXTURE" ) )
	{
		library = new TextureLibrary();
	}
	else{ _ASSERTE(!"UnknownLibraryType"); }

	return library;
}


void ColladaObject::GetLibrary(VECLIBRARYELEM& vecLibrary, LibraryElement::TYPE type) const
{
	for( VECLIBRARYELEM::const_iterator it = vecElemLibrary.begin(); it != vecElemLibrary.end(); ++it )
	{
		if( (*it)->TypeOf( type ) )
		{
			vecLibrary.push_back( *it );
		}
	}
}
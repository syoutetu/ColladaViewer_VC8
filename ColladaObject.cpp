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
#if _DEBUG	// �f�o�b�O���ɖ��O���`�F�b�N����ׂ�
		const XMLCh* name = currentNode->getNodeName();
#endif
		if( IsElementNode( currentNode ) )
		{
			if( Is_COLLADA_NodeName( currentNode ) )		// COLLADA�v�f�����������ꍇ
			{
				currentNode = currentNode->getFirstChild();		// �q�m�[�h����������
				continue;
			}
			else if( Is_asset_NodeName( currentNode ) )	// asset�v�f�����������ꍇ
			{
				_ASSERTE(elemAsset == NULL);		// �K��1���݂���̂ł��̎��_�ł�NULL

				elemAsset = new AssetElement();
				elemAsset->ReadNode( currentNode );
			}
			else if( Is_library_NodeName( currentNode ) )	// library�v�f�����������ꍇ
			{
				LibraryElement* elemLibrary = CreateLibraryElement( currentNode );
				if( elemLibrary != NULL )
				{
					elemLibrary->ReadNode( currentNode );
					vecElemLibrary.push_back( elemLibrary );
				}
			}
			else if( Is_scene_NodeName( currentNode ) )	// scene�v�f�����������ꍇ
			{
				_ASSERTE(elemScene == NULL);		// 0�܂���1���݂���̂ł��̎��_�ł�NULL

				elemScene = new SceneElement();
				elemScene->ReadNode( currentNode );
			}
		}

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}



// �K�v�ȗv�f���ǂݍ��܂�Ă���ꍇ��true��Ԃ�
// �v�f���s���S�ȏꍇ�̓G���[���b�Z�[�W��ݒ肵��false��Ԃ�
bool ColladaObject::ValidElements()
{
	strErrorMessage.clear();		// ���b�Z�[�W����������

	if( elemCollada == NULL ) { strErrorMessage += L"�E<COLLADA>�v�f��������܂���ł���\n"; }	// �K�����݂���

	if( elemAsset != NULL )
	{
		elemAsset->ValidElements( strErrorMessage );
	}
	else	// �K�����݂���
	{
		strErrorMessage += L"�E<asset>�v�f��������܂���ł���\n";
	}

	ValidElementsInContainer( vecElemLibrary, strErrorMessage );

	if( elemScene != NULL )
	{
		elemScene->ValidElements( strErrorMessage );
	}

	return strErrorMessage.empty();		// �G���[���Ȃ��ꍇ��true��Ԃ�
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
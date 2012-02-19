#include "stdafx.h"

#include "LightElement.h"



LightElement::LightElement()
{
	elemAsset = NULL;

	attrType = TYPE_POINT;		// デフォルト
}


LightElement::~LightElement()
{
	SAFE_DELETE(elemAsset);

	ClearVector( vecElemParam );
}



void LightElement::ReadNode(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	ReadAttributes( node );

	DOMNode* currentNode = node->getFirstChild();
	while( currentNode != NULL )
	{
#if _DEBUG	// デバッグ時に名前をチェックする為に
		const XMLCh* name = currentNode->getNodeName();
#endif

		if( IsElementNode( currentNode ) )
		{
			if( Is_asset_NodeName( currentNode ) )
			{
				_ASSERTE(elemAsset == NULL);		// 0または1つ存在するのでこの時点ではNULL

				elemAsset = new AssetElement();
				elemAsset->ReadNode( currentNode );
			}
			else if( Is_param_NodeName( currentNode ) )
			{
				ParamElement* elemParam = new ParamElement();
				
				elemParam->ReadNode( currentNode );
				vecElemParam.push_back( elemParam );
			}
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}



bool LightElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( elemAsset != NULL ) { elemAsset->ValidElements( str ); }

	if( vecElemParam.empty() ) { str += L"<param>要素が存在しません\n"; }

	ValidElementsInContainer( vecElemParam, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<light>\n" + str;
	}

	return str.empty();
}


void LightElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return ; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
	SetType( Get_type_Attribute( attr ) );
}


void LightElement::SetType(const XMLCh* type)
{
	_ASSERTE(type != NULL);

	if( XMLString::equals( type, (XMLCh*)L"AMBIENT" ) )
	{
		attrType = TYPE_AMBIENT;
	}
	else if( XMLString::equals( type , (XMLCh*)L"DIRECTIONAL" ) )
	{
		attrType = TYPE_DIRECTIONAL;
	}
	else if( XMLString::equals( type , (XMLCh*)L"POINT" ) )
	{
		attrType = TYPE_POINT;
	}
	else if( XMLString::equals( type , (XMLCh*)L"SPOT" ) )
	{
		attrType = TYPE_SPOT;
	}
}

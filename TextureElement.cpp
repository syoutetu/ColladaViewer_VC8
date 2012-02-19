#include "stdafx.h"

#include "TextureElement.h"



TextureElement::TextureElement()
{
	elemAsset = NULL;
}


TextureElement::~TextureElement()
{
	SAFE_DELETE(elemAsset);

	ClearVector( vecElemTechnique );
	ClearVector( vecElemParam );
}



void TextureElement::ReadNode(const DOMNode* node)
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
			else if( Is_technique_NodeName( currentNode ) )
			{
				TechniqueElement* elemTechnique = new TechniqueElement();
				
				elemTechnique->ReadNode( currentNode );
				vecElemTechnique.push_back( elemTechnique );
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



bool TextureElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( elemAsset != NULL ) { elemAsset->ValidElements( str ); }

	ValidElementsInContainer( vecElemParam, str );
	ValidElementsInContainer( vecElemTechnique, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<texture>\n" + str;
	}

	return str.empty();
}


void TextureElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return ; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
}


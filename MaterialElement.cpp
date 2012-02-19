#include "stdafx.h"

#include "MaterialElement.h"



MaterialElement::MaterialElement()
{
	elemAsset = NULL;
}


MaterialElement::~MaterialElement()
{
	SAFE_DELETE(elemAsset);

	ClearVector( vecElemShader );
	ClearVector( vecElemParam );
}



void MaterialElement::ReadNode(const DOMNode* node)
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
			else if( Is_shader_NodeName( currentNode ) )
			{
				ShaderElement* elemShader = new ShaderElement();

				elemShader->ReadNode( currentNode );
				vecElemShader.push_back( elemShader );
			}
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}



bool MaterialElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemShader.empty() ) { str += L"<shader>要素が存在しません\n"; }

	if( elemAsset != NULL ) { elemAsset->ValidElements( str ); }

	ValidElementsInContainer( vecElemParam, str );
	ValidElementsInContainer( vecElemShader, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<material>\n" + str;
	}

	return str.empty();
}


void MaterialElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
}
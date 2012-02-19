#include "stdafx.h"

#include "ShaderElement.h"



ShaderElement::ShaderElement()
{
}


ShaderElement::~ShaderElement()
{
	ClearVector( vecElemParam );
	ClearVector( vecElemTechnique );
}



void ShaderElement::ReadNode(const DOMNode* node)
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
			if( Is_param_NodeName( currentNode ) )
			{
				ParamElement* elemParam = new ParamElement();
				
				elemParam->ReadNode( currentNode );
				vecElemParam.push_back( elemParam );
			}
			else if( Is_technique_NodeName( currentNode ) )
			{
				TechniqueElement* elemTech = new TechniqueElement();

				elemTech->ReadNode( currentNode );
				vecElemTechnique.push_back( elemTech );
			}
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}


bool ShaderElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemTechnique.empty() ) { str += L"<technique>要素が存在しません\n"; }

	ValidElementsInContainer( vecElemParam, str );
	ValidElementsInContainer( vecElemTechnique, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<shader>\n" + str;
	}

	return str.empty();
}


void ShaderElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return ; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
}

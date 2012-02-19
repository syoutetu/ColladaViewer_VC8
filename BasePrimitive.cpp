#include "stdafx.h"

#include "BasePrimitive.h"



BasePrimitive::BasePrimitive()
{
	attrCount = (unsigned int)-1;		// 初期化
}


BasePrimitive::~BasePrimitive()
{
}




void BasePrimitive::ReadNode(const DOMNode* node)
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
			if( Is_input_NodeName( currentNode ) )
			{
				InputElement* elemInput = new InputElement();

				elemInput->ReadNode( currentNode );
				vecElemInput.push_back( elemInput );
			}
			else if( Is_p_NodeName( currentNode ) )
			{
				PrimitiveElement* elemP = new PrimitiveElement();

				elemP->ReadNode( currentNode );
				vecElemP.push_back( elemP );
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



bool BasePrimitive::ValidElements(std::wstring& message, const wchar_t* nodeName) const
{
	_ASSERTE(nodeName != NULL);

	std::wstring str;

	if( attrCount == (unsigned int)-1 ) { str +=  L"count属性が存在しません\n"; }
	_ASSERTE(attrCount == GetPrimitiveCount());

	ValidElementsInContainer( vecElemInput, str );
	ValidElementsInContainer( vecElemParam, str );
	ValidElementsInContainer( vecElemP, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L'<';
		message += nodeName;
		message += L">\n";
		message += str;
	}

	return str.empty();
}



InputElement* BasePrimitive::GetInputElementByAttrIdx(unsigned int idx) const
{
	for( VECINPUTELEM::const_iterator it = vecElemInput.begin(); it != vecElemInput.end(); ++it )
	{
		if( (*it)->GetIdxAttribute() == idx )
		{
			return *it;
		}
	}

	return NULL;
}





void BasePrimitive::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetUIntValue( attrCount, Get_count_Attribute( attr ) );
	SetStringValue( attrMaterial, Get_material_Attribute( attr ) );
}

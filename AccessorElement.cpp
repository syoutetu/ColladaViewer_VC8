#include "stdafx.h"

#include "AccessorElement.h"



AccessorElement::AccessorElement()
{
	attrCount = (unsigned int)-1;		// 初期化
	attrOffset = 0;		// デフォルト
	attrStride = 1;		// デフォルト
}


AccessorElement::~AccessorElement()
{
	ClearVector( vecElemParam );
}



void AccessorElement::ReadNode(const DOMNode* node)
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
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}



bool AccessorElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( attrCount == (unsigned int)-1 ) { str += L"count属性が存在しません\n"; }
	if( attrSource.empty() ) { str += L"source属性が存在しません\n"; }

	ValidElementsInContainer( vecElemParam, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<accessor>\n" + str;
	}

	return str.empty();
}


void AccessorElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return ; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetUIntValue( attrCount, Get_count_Attribute( attr ) );
	SetUIntValue( attrOffset, Get_offset_Attribute( attr ) );
	SetStringValue( attrSource, Get_source_Attribute( attr ) );
	SetUIntValue( attrStride, Get_stride_Attribute( attr ) );
}
#include "stdafx.h"

#include "ImageElement.h"



ImageElement::ImageElement()
{
	attrHeight = 0;		// 初期化
	attrWidth = 0;		// 初期化
	attrDepth = 1;		// デフォルト
}


ImageElement::~ImageElement()
{
}



void ImageElement::ReadNode(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	ReadAttributes( node );
}



bool ImageElement::ValidElements(std::wstring& message) const
{
	return true;
}


void ImageElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return ; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
	SetStringValue( attrSource, Get_source_Attribute( attr ) );
	SetStringValue( attrFormat, Get_format_Attribute( attr ) );
	SetUIntValue( attrHeight, Get_height_Attribute( attr ) );
	SetUIntValue( attrWidth, Get_width_Attribute( attr ) );
	SetUIntValue( attrDepth, Get_depth_Attribute( attr ) );
}


#include "stdafx.h"

#include "ArrayElement.h"



ArrayElement::ArrayElement()
{
	attrCount = (unsigned int)-1;		// 初期化
	attrMinInclusive = MIN_INCLUSIVE;	// デフォルト
	attrMaxInclusive = MAX_INCLUSIVE;	// デフォルト
	attrDigits = DIGITS;				// デフォルト
	attrMagnitude = MAGNITUDE;			// デフォルト
}


ArrayElement::~ArrayElement()
{
}



void ArrayElement::ReadNode(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	ReadAttributes( node );

}


bool ArrayElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	str += L"<array>要素は未実装です\n";	// 未実装
	
	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<array>\n" + str;
	}

	return str.empty();;
}


void ArrayElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetUIntValue( attrCount, Get_count_Attribute( attr ) );
	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
	SetStringValue( attrType, Get_type_Attribute( attr ) );
	SetIntValue( attrMinInclusive, Get_MinInclusive_Attribute( attr ) );
	SetIntValue( attrMaxInclusive, Get_MaxInclusive_Attribute( attr ) );
	SetIntValue( attrDigits, Get_digits_Attribute( attr ) );
	SetIntValue( attrMagnitude, Get_magnitude_Attribute( attr ) );
}

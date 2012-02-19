#include "stdafx.h"

#include "ArrayElement.h"



ArrayElement::ArrayElement()
{
	attrCount = (unsigned int)-1;		// ������
	attrMinInclusive = MIN_INCLUSIVE;	// �f�t�H���g
	attrMaxInclusive = MAX_INCLUSIVE;	// �f�t�H���g
	attrDigits = DIGITS;				// �f�t�H���g
	attrMagnitude = MAGNITUDE;			// �f�t�H���g
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

	str += L"<array>�v�f�͖������ł�\n";	// ������
	
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

#include "stdafx.h"

#include "IntArrayElement.h"



IntArrayElement::IntArrayElement()
{
	attrCount = (unsigned int)-1;		// 初期化
	attrMinInclusive = MIN_INCLUSIVE;	// デフォルト
	attrMaxInclusive = MAX_INCLUSIVE;	// デフォルト
}


IntArrayElement::~IntArrayElement()
{
}



void IntArrayElement::ReadNode(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	ReadAttributes( node );

	ReadValue( node );
}


bool IntArrayElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( attrCount == (unsigned int)-1 ) { str +=  L"count属性が存在しません\n"; }
	_ASSERTE(attrCount == GetCount());

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<int_array>\n" + str;
	}

	return str.empty();
}


void IntArrayElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetUIntValue( attrCount, Get_count_Attribute( attr ) );
	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
	SetIntValue( attrMinInclusive, Get_MinInclusive_Attribute( attr ) );
	SetIntValue( attrMaxInclusive, Get_MaxInclusive_Attribute( attr ) );
}


void IntArrayElement::ReadValue(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	if( attrCount == (unsigned int)-1 ) { return; }
	valInt.reserve( attrCount );

	DOMNode* value = node->getFirstChild();
	if( value == NULL ) { return; }

	const XMLCh* strVal = value->getNodeValue();
	if( strVal == NULL ) { return; }

	while( *strVal++ != L'\0' )
	{
		XMLCh buffer[32];
		unsigned int index = 0;
			
		while( *strVal != L' ' && *strVal != L'\t' && *strVal != L'\n' && *strVal != L'\r' && *strVal != L'\0' && index < 31 )
		{
			buffer[index++] = *strVal++;
		}

		buffer[index] = L'\0';
		
		if( index == 0 ) { continue; }

		valInt.push_back( XMLChToInt( buffer ) );
	}
}

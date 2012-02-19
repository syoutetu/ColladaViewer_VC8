#include "stdafx.h"

#include "FloatArrayElement.h"



FloatArrayElement::FloatArrayElement()
{
	attrCount = (unsigned int)-1;	// 初期化
	attrDigits = DIGITS;			// デフォルト
	attrMagnitude = MAGNITUDE;		// デフォルト
}


FloatArrayElement::~FloatArrayElement()
{
}



void FloatArrayElement::ReadNode(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	ReadAttributes( node );

	ReadValue( node );
}


bool FloatArrayElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( attrCount == (unsigned int)-1 ) { str +=  L"count属性が存在しません\n"; }
	_ASSERTE(attrCount == GetCount());

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<float_array>\n" + str;
	}

	return str.empty();
}


void FloatArrayElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetUIntValue( attrCount, Get_count_Attribute( attr ) );
	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
	SetIntValue( attrDigits, Get_digits_Attribute( attr ) );
	SetIntValue( attrMagnitude, Get_magnitude_Attribute( attr ) );
}



void FloatArrayElement::ReadValue(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	if( attrCount == (unsigned int)-1 ) { return; }
	valFloat.reserve( attrCount );

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

		valFloat.push_back( XMLChToFloat( buffer ) );
	}
}

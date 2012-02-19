#include "stdafx.h"

#include "BoolArrayElement.h"



BoolArrayElement::BoolArrayElement()
{
	attrCount = (unsigned int)-1;		// ‰Šú‰»
}


BoolArrayElement::~BoolArrayElement()
{
}



void BoolArrayElement::ReadNode(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	ReadAttributes( node );

	ReadValue( node );
}


bool BoolArrayElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( attrCount == (unsigned int)-1 ) { str +=  L"count‘®«‚ª‘¶İ‚µ‚Ü‚¹‚ñ\n"; }
	_ASSERTE(attrCount == GetCount());

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<bool_array>\n" + str;
	}

	return str.empty();
}


void BoolArrayElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetUIntValue( attrCount, Get_count_Attribute( attr ) );
	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
}



void BoolArrayElement::ReadValue(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	if( attrCount == (unsigned int)-1 ) { return; }
	valBool.reserve( attrCount );

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

		valBool.push_back( XMLChToBool( buffer ) );
	}
}

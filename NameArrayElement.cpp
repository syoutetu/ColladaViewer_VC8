#include "stdafx.h"

#include "NameArrayElement.h"



NameArrayElement::NameArrayElement()
{
	attrCount = (unsigned int)-1;		// ‰Šú‰»
}


NameArrayElement::~NameArrayElement()
{
}



void NameArrayElement::ReadNode(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	ReadAttributes( node );

	ReadValue( node );
}


bool NameArrayElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( attrCount == (unsigned int)-1 ) { str +=  L"count‘®«‚ª‘¶İ‚µ‚Ü‚¹‚ñ\n"; }
	_ASSERTE(attrCount == GetCount());

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<Name_array>\n" + str;
	}

	return str.empty();
}


void NameArrayElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetUIntValue( attrCount, Get_count_Attribute( attr ) );
	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
}


void NameArrayElement::ReadValue(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	if( attrCount == (unsigned int)-1 ) { return; }
	valName.reserve( attrCount );

	DOMNode* value = node->getFirstChild();
	if( value == NULL ) { return; }

	_ASSERTE(sizeof(XMLCh) == sizeof(wchar_t));
	const wchar_t* strVal = (const wchar_t*)value->getNodeValue();
	if( strVal == NULL ) { return; }

	while( *strVal++ != L'\0' )
	{
		wchar_t buffer[32];
		unsigned int index = 0;
			
		while( *strVal != L' ' && *strVal != L'\t' && *strVal != L'\n' && *strVal != L'\r' && *strVal != L'\0' && index < 31 )
		{
			buffer[index++] = *strVal++;
		}

		buffer[index] = L'\0';
		
		if( index == 0 ) { continue; }

		valName.push_back( buffer );
	}
}

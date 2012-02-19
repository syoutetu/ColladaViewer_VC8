#include "stdafx.h"

#include "CodeElement.h"



CodeElement::CodeElement()
{
}


CodeElement::~CodeElement()
{
}



void CodeElement::ReadNode(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	ReadAttributes( node );
}


bool CodeElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( attrLang.empty() ) { str += L"lang‘®«‚ª‘¶İ‚µ‚Ü‚¹‚ñ\n"; }

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<code>\n" + str;
	}

	return str.empty();
}


void CodeElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return ; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrLang, Get_lang_Attribute( attr ) );
	SetStringValue( attrProfile, Get_profile_Attribute( attr ) );
	SetStringValue( attrSemantic, Get_semantic_Attribute( attr ) );
	SetStringValue( attrUrl, Get_url_Attribute( attr ) );
}


void CodeElement::ReadValue(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNode* value = node->getFirstChild();
	if( value == NULL ) { return; }

	valCode = (const wchar_t*)value->getNodeValue();
}


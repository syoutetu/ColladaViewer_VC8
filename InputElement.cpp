#include "stdafx.h"

#include "InputElement.h"



InputElement::InputElement()
{
	attrIdx = (unsigned int)-1;		// ‰Šú‰»
}


InputElement::~InputElement()
{
}




void InputElement::ReadNode(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	ReadAttributes( node );
}



bool InputElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( attrSemantic.empty() ) { str += L"semantic‘®«‚ª‘¶İ‚µ‚Ü‚¹‚ñ\n"; }
	if( attrSource.empty() ) { str += L"source‘®«‚ª‘¶İ‚µ‚Ü‚¹‚ñ\n";  }

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<input>\n" + str;
	}

	return str.empty();
}


void InputElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return ; }

	SetUIntValue( attrIdx, Get_idx_Attribute( attr ) );
	SetStringValue( attrSemantic, Get_semantic_Attribute( attr ) );
	SetStringValue( attrSource, Get_source_Attribute( attr ) );
}
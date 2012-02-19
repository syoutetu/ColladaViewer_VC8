#include "stdafx.h"

#include "InstanceElement.h"



InstanceElement::InstanceElement()
{
}


InstanceElement::~InstanceElement()
{
}



void InstanceElement::ReadNode(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	ReadAttributes( node );
}


bool InstanceElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( attrUrl.empty() ) { str += L"url‘®«‚ª‘¶İ‚µ‚Ü‚¹‚ñ\n"; }

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<instance>\n" + str;
	}

	return str.empty();
}


void InstanceElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetStringValue( attrUrl, Get_url_Attribute( attr ) );
}

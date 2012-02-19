#include "stdafx.h"

#include "ChannelElement.h"



ChannelElement::ChannelElement()
{
}


ChannelElement::~ChannelElement()
{
}



void ChannelElement::ReadNode(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	ReadAttributes( node );
}


bool ChannelElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( attrSource.empty() ) { str += L"source‘®«‚ª‘¶İ‚µ‚Ü‚¹‚ñ\n"; }
	if( attrTarget.empty() ) { str += L"target‘®«‚ª‘¶İ‚µ‚Ü‚¹‚ñ\n"; }

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<channel>\n" + str;
	}

	return str.empty();
}


void ChannelElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
	SetStringValue( attrSource, Get_source_Attribute( attr ) );
	SetStringValue( attrTarget, Get_target_Attribute( attr ) );
}

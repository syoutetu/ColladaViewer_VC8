#include "stdafx.h"

#include "BaseValue.h"



BaseValue::BaseValue(unsigned int reqCount): requiredCount( reqCount )
{
}


BaseValue::~BaseValue()
{
}



void BaseValue::ReadNode(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	ReadAttributes( node );

	ReadValue( node );
}


bool BaseValue::ValidElements(std::wstring& message, const wchar_t* nodeName) const
{
	_ASSERTE(nodeName != NULL);

	std::wstring str;

	if( GetCount() < requiredCount ) { str += L"ƒm[ƒh‚Ì’l‚Ì”‚ª‘«‚è‚Ü‚¹‚ñ\n"; }

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L'<';
		message += nodeName;
		message += L">\n";
		message += str;
	}

	return str.empty();
}


void BaseValue::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetStringValue( attrSubId, Get_sid_Attribute( attr ) );
}


void BaseValue::ReadValue(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNode* value = node->getFirstChild();
	if( value == NULL ) { return; }

	BaseRefVectorOf<XMLCh>* vecValue = XMLString::tokenizeString( value->getNodeValue() );

	unsigned int sizeValue = vecValue->size();
	if( sizeValue == 0 ) { return; }

	valParam.reserve( sizeValue );
	for( unsigned int i = 0; i < sizeValue; i++ )
	{
		valParam.push_back( XMLChToFloat( vecValue->elementAt( i ) ) );
	}

	SAFE_DELETE(vecValue);
}

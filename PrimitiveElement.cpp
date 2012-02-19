#include "stdafx.h"

#include "PrimitiveElement.h"



PrimitiveElement::PrimitiveElement()
{
}


PrimitiveElement::~PrimitiveElement()
{
}



void PrimitiveElement::ReadNode(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	ReadValue( node );
}


bool PrimitiveElement::ValidElements(std::wstring& message) const
{
	return true;
}



void PrimitiveElement::ReadValue(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNode* value = node->getFirstChild();
	if( value == NULL ) { return; }

	BaseRefVectorOf<XMLCh>* vecValue = XMLString::tokenizeString( value->getNodeValue() );

	unsigned int sizeValue = vecValue->size();
	if( sizeValue == 0 ) { return; }

	valIndices.reserve( sizeValue );
	for( unsigned int i = 0; i < sizeValue; i++ )
	{
		valIndices.push_back( XMLChToInt( vecValue->elementAt( i ) ) );
	}

	SAFE_DELETE(vecValue);
}
#include "stdafx.h"

#include "ParamElement.h"



ParamElement::ParamElement()
{
	attrFlow = FLOW_Null;		// èâä˙âª
	attrType = TYPE_Null;		// èâä˙âª
}


ParamElement::~ParamElement()
{
}



void ParamElement::ReadNode(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	ReadAttributes( node );

	ReadValue( node );
}


bool ParamElement::ValidElements(std::wstring& message) const
{
	std::wstring str;
	
	if( attrType == TYPE_Null ) { str += L"typeëÆê´Ç™ë∂ç›ÇµÇ‹ÇπÇÒ\n"; }

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<param>\n" + str;
	}

	return str.empty();
}


unsigned int ParamElement::GetSize() const
{
	if( IsBoolType() )	{ return (unsigned int)valBool.size(); }
	if( IsFloatType() )	{ return (unsigned int)valFloat.size(); }
	return 0;
}


void ParamElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
	SetFlow( Get_flow_Attribute( attr ) );
	SetStringValue( attrSemantic, Get_semantic_Attribute( attr ) );
	SetType( Get_type_Attribute( attr ) );
	SetStringValue( attrSubId, Get_sid_Attribute( attr ) );
}


void ParamElement::SetFlow(const XMLCh* flow)
{
	_ASSERTE(flow != NULL);

	if( XMLString::equals( flow, (XMLCh*)L"IN" ) )
	{
		attrFlow = FLOW_IN;
	}
	else if( XMLString::equals( flow, (XMLCh*)L"OUT" ) )
	{
		attrFlow = FLOW_OUT;
	}
	else if( XMLString::equals( flow, (XMLCh*)L"INOUT" ) )
	{
		attrFlow = FLOW_INOUT;
	}
}


void ParamElement::SetType(const XMLCh* type)
{
	_ASSERTE(type != NULL);

	if( XMLString::equals( type, (XMLCh*)L"bool" ) )
	{
		attrType = TYPE_BOOL;
	}
	else if( XMLString::equals( type , (XMLCh*)L"float" ) )
	{
		attrType = TYPE_FLOAT;
	}
	else if( XMLString::equals( type , (XMLCh*)L"float2" ) )
	{
		attrType = TYPE_FLOAT2;
	}
	else if( XMLString::equals( type , (XMLCh*)L"float3" ) )
	{
		attrType = TYPE_FLOAT3;
	}
	else if( XMLString::equals( type , (XMLCh*)L"float4" ) )
	{
		attrType = TYPE_FLOAT4;
	}
	else if( XMLString::equals( type , (XMLCh*)L"blend" ) )
	{
		attrType = TYPE_BLEND;
	}
	else if( XMLString::equals( type , (XMLCh*)L"function" ) )
	{
		attrType = TYPE_FUNCTION;
	}
}


void ParamElement::ReadValue(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNode* value = node->getFirstChild();
	if( value == NULL ) { return; }

	BaseRefVectorOf<XMLCh>* vecValue = XMLString::tokenizeString( value->getNodeValue() );

	unsigned int sizeValue = vecValue->size();
	if( sizeValue == 0 ) { return; }

	if( IsFloatType() )
	{
		valFloat.reserve( sizeValue );
		for( unsigned int i = 0; i < sizeValue; i++ )
		{
			valFloat.push_back( XMLChToFloat( vecValue->elementAt( i ) ) );
		}
	}
	else if( IsBoolType() )
	{
		valBool.reserve( sizeValue );
		for( unsigned int i = 0; i < sizeValue; i++ )
		{
			valBool.push_back( XMLChToBool( vecValue->elementAt( i ) ) );
		}
	}
	else if( IsBlendType() )
	{
		// ñ¢é¿ëï
	}
	else if( IsFunctionType() )
	{
		// ñ¢é¿ëï
	}
	else { _ASSERTE(!"UnknownType"); }

	SAFE_DELETE(vecValue);
}
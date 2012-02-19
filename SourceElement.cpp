#include "stdafx.h"

#include "SourceElement.h"



SourceElement::SourceElement()
{
}


SourceElement::~SourceElement()
{
	ClearVector(vecElemArray);
	ClearVector(vecElemBoolArray);
	ClearVector(vecElemFloatArray);
	ClearVector(vecElemIntArray);
	ClearVector(vecElemNameArray);
	ClearVector(vecElemTechnique);
}



void SourceElement::ReadNode(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	ReadAttributes( node );

	DOMNode* currentNode = node->getFirstChild();
	while( currentNode != NULL )
	{
#if _DEBUG	// �f�o�b�O���ɖ��O���`�F�b�N����ׂ�
		const XMLCh* name = currentNode->getNodeName();
#endif

		if( IsElementNode( currentNode ) )
		{
			if( Is_array_NodeName( currentNode ) )
			{
				ArrayElement* elemArray = new ArrayElement();

				elemArray->ReadNode( currentNode );
				vecElemArray.push_back( elemArray );
			}
			else if( Is_bool_array_NodeName( currentNode ) )
			{
				BoolArrayElement* elemBoolArray = new BoolArrayElement();

				elemBoolArray->ReadNode( currentNode );
				vecElemBoolArray.push_back( elemBoolArray );
			}
			else if( Is_float_array_NodeName( currentNode ) )
			{
				FloatArrayElement* elemFloatArray = new FloatArrayElement();

				elemFloatArray->ReadNode( currentNode );
				vecElemFloatArray.push_back( elemFloatArray );
			}
			else if( Is_int_array_NodeName( currentNode ) )
			{
				IntArrayElement* elemIntArray = new IntArrayElement();

				elemIntArray->ReadNode( currentNode );
				vecElemIntArray.push_back( elemIntArray );
			}
			else if( Is_Name_array_NodeName( currentNode ) )
			{
				NameArrayElement* elemNameArray = new NameArrayElement();

				elemNameArray->ReadNode( currentNode );
				vecElemNameArray.push_back( elemNameArray );
			}
			else if( Is_technique_NodeName( currentNode ) )
			{
				TechniqueElement* elemTechnique = new TechniqueElement();

				elemTechnique->ReadNode( currentNode );
				vecElemTechnique.push_back( elemTechnique );
			}
		}

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}


bool SourceElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	ValidElementsInContainer( vecElemArray, str );
	ValidElementsInContainer( vecElemBoolArray, str );
	ValidElementsInContainer( vecElemFloatArray, str );
	ValidElementsInContainer( vecElemIntArray, str );
	ValidElementsInContainer( vecElemNameArray, str );
	ValidElementsInContainer( vecElemTechnique, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<source>\n" + str;
	}

	return str.empty();
}



// accessor�v�f�Ŏw�肳��Ă���bool_array�v�f���擾����
BoolArrayElement* SourceElement::GetBoolArrayElement(const AccessorElement* elemAccessor) const
{
	std::wstring strSource = elemAccessor->GetSourceAttribute();
	if( strSource.empty() ) { return NULL; }

	TrimFirstSharpChar( strSource );

	for( VECBOOLAELEM::const_iterator it = vecElemBoolArray.begin(); it != vecElemBoolArray.end(); ++it )
	{
		if( (*it)->GetIdAttribute().compare( strSource ) == 0 )
		{
			return *it;
		}
	}

	return NULL;
}

// accessor�v�f�Ŏw�肳��Ă���float_array�v�f���擾����
FloatArrayElement* SourceElement::GetFloatArrayElement(const AccessorElement* elemAccessor) const
{
	std::wstring strSource = elemAccessor->GetSourceAttribute();
	if( strSource.empty() ) { return NULL; }

	TrimFirstSharpChar( strSource );

	for( VECFLOATAELEM::const_iterator it = vecElemFloatArray.begin(); it != vecElemFloatArray.end(); ++it )
	{
		if( (*it)->GetIdAttribute().compare( strSource ) == 0 )
		{
			return *it;
		}
	}

	return NULL;
}

// accessor�v�f�Ŏw�肳��Ă���int_array�v�f���擾����
IntArrayElement* SourceElement::GetIntArrayElement(const AccessorElement* elemAccessor) const
{
	std::wstring strSource = elemAccessor->GetSourceAttribute();
	if( strSource.empty() ) { return NULL; }

	TrimFirstSharpChar( strSource );

	for( VECINTAELEM::const_iterator it = vecElemIntArray.begin(); it != vecElemIntArray.end(); ++it )
	{
		if( (*it)->GetIdAttribute().compare( strSource ) == 0 )
		{
			return *it;
		}
	}

	return NULL;
}


// profile������COMMON��technique�v�f���擾����
TechniqueElement* SourceElement::GetTechniqueOfCommonProfile() const
{
	for( VECTECHNIQUEELEM::const_iterator it = vecElemTechnique.begin(); it != vecElemTechnique.end(); ++it )
	{
		if( (*it)->GetProfileAttribute().compare( L"COMMON" ) == 0 )
		{
			return *it;
		}
	}

	return NULL;
}



void SourceElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
}

#include "stdafx.h"

#include "SkinElement.h"



SkinElement::SkinElement()
{
	elemVertices = NULL;
}


SkinElement::~SkinElement()
{
	SAFE_DELETE(elemVertices);

	ClearVector( vecElemSource );
}



void SkinElement::ReadNode(const DOMNode* node)
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
			if( Is_source_NodeName( currentNode ) )
			{
				SourceElement* elemSource = new SourceElement();
				
				elemSource->ReadNode( currentNode );
				vecElemSource.push_back( elemSource );
			}
			else if( Is_vertices_NodeName( currentNode ) )
			{
				_ASSERTE(elemVertices == NULL);		// �K��1���݂���̂ł��̎��_�ł�NULL
				
				elemVertices = new VerticesElement();
				elemVertices->ReadNode( currentNode );
			}
		}

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}



bool SkinElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemSource.empty() ) { str += L"<source>�v�f�����݂��܂���\n"; }

	if( elemVertices != NULL ) { elemVertices->ValidElements( str ); }
	else { str += L"<vertices>�v�f�����݂��܂���\n";  }

	ValidElementsInContainer( vecElemSource, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<skin>\n" + str;
	}

	return str.empty();
}


void SkinElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return ; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
}

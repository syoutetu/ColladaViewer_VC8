#include "stdafx.h"

#include "GeometryElement.h"



GeometryElement::GeometryElement()
{
	elemMesh = NULL;
}


GeometryElement::~GeometryElement()
{
	SAFE_DELETE(elemMesh);

	ClearVector( vecElemExtra );
}



void GeometryElement::ReadNode(const DOMNode* node)
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
			if( Is_mesh_NodeName( currentNode ) )
			{
				_ASSERTE(elemMesh == NULL);		// �K��1���݂���̂ł��̎��_�ł�NULL

				elemMesh = new MeshElement();
				elemMesh->ReadNode( currentNode );
			}
			else if( Is_extra_NodeName( currentNode ) )
			{
				ExtraElement* elemExtra = new ExtraElement();

				elemExtra->ReadNode( currentNode );
				vecElemExtra.push_back( elemExtra );
			}
		}

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}



bool GeometryElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( elemMesh != NULL ) { elemMesh->ValidElements( str ); }
	else { str += L"<mesh>�v�f�����݂��܂���\n"; }

	ValidElementsInContainer( vecElemExtra, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<geometry>�v�f�ɃG���[������܂�\n" + str;
	}

	return str.empty();
}


void GeometryElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
}
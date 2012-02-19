#include "stdafx.h"

#include "AccessorElement.h"



AccessorElement::AccessorElement()
{
	attrCount = (unsigned int)-1;		// ������
	attrOffset = 0;		// �f�t�H���g
	attrStride = 1;		// �f�t�H���g
}


AccessorElement::~AccessorElement()
{
	ClearVector( vecElemParam );
}



void AccessorElement::ReadNode(const DOMNode* node)
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
			if( Is_param_NodeName( currentNode ) )
			{
				ParamElement* elemParam = new ParamElement();
				
				elemParam->ReadNode( currentNode );
				vecElemParam.push_back( elemParam );
			}
		}

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}



bool AccessorElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( attrCount == (unsigned int)-1 ) { str += L"count���������݂��܂���\n"; }
	if( attrSource.empty() ) { str += L"source���������݂��܂���\n"; }

	ValidElementsInContainer( vecElemParam, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<accessor>\n" + str;
	}

	return str.empty();
}


void AccessorElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return ; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetUIntValue( attrCount, Get_count_Attribute( attr ) );
	SetUIntValue( attrOffset, Get_offset_Attribute( attr ) );
	SetStringValue( attrSource, Get_source_Attribute( attr ) );
	SetUIntValue( attrStride, Get_stride_Attribute( attr ) );
}
#include "stdafx.h"

#include "ProgramElement.h"



ProgramElement::ProgramElement()
{
	elemAsset = NULL;
	elemCode = NULL;
	elemEntry = NULL;
}


ProgramElement::~ProgramElement()
{
	SAFE_DELETE(elemAsset);
	SAFE_DELETE(elemCode);
	SAFE_DELETE(elemEntry);

	ClearVector( vecElemParam );
}




void ProgramElement::ReadNode(const DOMNode* node)
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
			if( Is_asset_NodeName( currentNode ) )
			{
				_ASSERTE(elemAsset == NULL);		// 0�܂���1���݂���̂ł��̎��_�ł�NULL
				
				elemAsset = new AssetElement();
				elemAsset->ReadNode( currentNode );
			}
			else if( Is_code_NodeName( currentNode ) )
			{
				_ASSERTE(elemCode == NULL);		// 0�܂���1���݂���̂ł��̎��_�ł�NULL

				elemCode = new CodeElement();
				elemCode->ReadNode( currentNode );
			}
			else if( Is_entry_NodeName( currentNode ) )
			{
				_ASSERTE(elemEntry == NULL);		// 0�܂���1���݂���̂ł��̎��_�ł�NULL

				elemEntry = new EntryElement();
				elemEntry->ReadNode( currentNode );
			}
			else if( Is_param_NodeName( currentNode ) )
			{
				ParamElement* elemParam = new ParamElement();
				
				elemParam->ReadNode( currentNode );
				vecElemParam.push_back( elemParam );
			}
		}

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}



bool ProgramElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( elemAsset != NULL ) { elemAsset->ValidElements( str ); }
	if( elemCode != NULL ) { elemCode->ValidElements( str ); }
	if( elemEntry != NULL ) { elemEntry->ValidElements( str ); }

	ValidElementsInContainer( vecElemParam, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<program>\n" + str;
	}

	return str.empty();
}



void ProgramElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
	SetStringValue( attrUrl, Get_url_Attribute( attr ) );
}
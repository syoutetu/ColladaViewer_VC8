#include "stdafx.h"

#include "AssetElement.h"



AssetElement::AssetElement()
{
	attrUnitMeter = 1.0f;		// デフォルト
	elemUpAxis = AXIS_Y;		// デフォルト
}




void AssetElement::ReadNode(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNode* currentNode = node->getFirstChild();
	while( currentNode != NULL )
	{
#if _DEBUG	// デバッグ時に名前をチェックする為に
		const XMLCh* name = currentNode->getNodeName();
#endif

		if( IsElementNode( currentNode ) )
		{
			if( Is_author_NodeName( currentNode ) )
			{
				GetFirstChildNodeValue( currentNode, elemAuthor );
			}
			else if( Is_authoring_tool_NodeName( currentNode ) )
			{
				GetFirstChildNodeValue( currentNode, elemAuthoringTool );
			}
			else if( Is_created_NodeName( currentNode ) )
			{
				GetFirstChildNodeValue( currentNode, elemCreated );
			}
			else if( Is_modified_NodeName( currentNode ) )
			{
				GetFirstChildNodeValue( currentNode, elemModified );
			}
			else if( Is_revision_NodeName( currentNode ) )
			{
				GetFirstChildNodeValue( currentNode, elemRevision );
			}
			else if( Is_source_data_NodeName( currentNode ) )
			{
				GetFirstChildNodeValue( currentNode, elemSourceData );
			}
			else if( Is_copyright_NodeName( currentNode ) )
			{
				GetFirstChildNodeValue( currentNode, elemCopyright );
			}
			else if( Is_title_NodeName( currentNode ) )
			{
				GetFirstChildNodeValue( currentNode, elemTitle );
			}
			else if( Is_subject_NodeName( currentNode ) )
			{
				GetFirstChildNodeValue( currentNode, elemSubject );
			}
			else if( Is_keywords_NodeName( currentNode ) )
			{
				GetFirstChildNodeValue( currentNode, elemKeywords );
			}
			else if( Is_comments_NodeName( currentNode ) )
			{
				GetFirstChildNodeValue( currentNode, elemComments );
			}
			else if( Is_unit_NodeName( currentNode ) )
			{
				ReadUnitAttributes( currentNode );
			}
			else if( Is_up_axis_NodeName( currentNode ) )
			{
				if( currentNode->hasChildNodes() )
				{
					SetUpAxis( currentNode->getFirstChild()->getNodeValue() );
				}
			}
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}



bool AssetElement::ValidElements(std::wstring& message) const
{
	return true;
}


void AssetElement::SetUpAxis(const XMLCh* up)
{
	if( XMLString::equals( up, (XMLCh*)L"X_UP" ) )
	{
		elemUpAxis = AXIS_X;
	}
	else if( XMLString::equals( up, (XMLCh*)L"Y_UP" ) )
	{
		elemUpAxis = AXIS_Y;
	}
	else if( XMLString::equals( up, (XMLCh*)L"Z_UP" ) )
	{
		elemUpAxis = AXIS_Z;
	}
	else { _ASSERTE(!"UnknownUpAxis"); }
}


void AssetElement::ReadUnitAttributes(const DOMNode* nodeUnit)
{
	_ASSERTE(nodeUnit != NULL);

	DOMNamedNodeMap* attr = nodeUnit->getAttributes();
	if( attr == NULL ) { return; }

	SetStringValue( elemUnitName, Get_name_Attribute( attr ) );
	SetStringValue( elemUnitMeter, Get_meter_Attribute( attr ) );

	if( elemUnitMeter.empty() == false )
	{
		attrUnitMeter = XMLChToFloat( (const XMLCh*)elemUnitMeter.c_str() );
	}
}
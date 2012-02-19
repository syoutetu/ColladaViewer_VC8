#include "stdafx.h"

#include "VerticesElement.h"



VerticesElement::VerticesElement()
{
}


VerticesElement::~VerticesElement()
{
	ClearVector(vecElemInput);
}



void VerticesElement::ReadNode(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	ReadAttributes( node );

	DOMNode* currentNode = node->getFirstChild();
	while( currentNode != NULL )
	{
#if _DEBUG	// デバッグ時に名前をチェックする為に
		const XMLCh* name = currentNode->getNodeName();
#endif

		if( IsElementNode( currentNode ) )
		{
			if( Is_input_NodeName( currentNode ) )
			{
				InputElement* elemInput = new InputElement();

				elemInput->ReadNode( currentNode );
				vecElemInput.push_back( elemInput );
			}
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}


bool VerticesElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemInput.empty() ) { str += L"<input>要素が存在しません\n"; }

	ValidElementsInContainer( vecElemInput, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<vertices>\n" + str;
	}

	return str.empty();
}


InputElement* VerticesElement::GetInputElementBySemantic(const std::wstring& semantic) const
{
	for( VECINPUTELEM::const_iterator it = vecElemInput.begin(); it != vecElemInput.end(); ++it )
	{
		if( (*it)->GetSemanticAttribute().compare( semantic ) == 0 )
		{
			return *it;
		}
	}

	return NULL;
}



void VerticesElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
	SetUIntValue( attrCount, Get_count_Attribute( attr ) );
}

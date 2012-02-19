#include "stdafx.h"

#include "JointsElement.h"



JointsElement::JointsElement()
{
	attrCount = 0;		// 初期化
}


JointsElement::~JointsElement()
{
	ClearVector(vecElemInput);
}



void JointsElement::ReadNode(const DOMNode* node)
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


bool JointsElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemInput.size() < 2 ) { str += L"<input>要素が2つ以上存在しません\n"; }

	ValidElementsInContainer( vecElemInput, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<joints>\n" + str;
	}

	return str.empty();
}


void JointsElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
	SetUIntValue( attrCount, Get_count_Attribute( attr ) );
}

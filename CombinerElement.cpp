#include "stdafx.h"

#include "CombinerElement.h"



CombinerElement::CombinerElement()
{
	attrCount = (unsigned int)-1;
}


CombinerElement::~CombinerElement()
{	
	ClearVector(vecElemInput);
	ClearVector(vecElemValue);
}



void CombinerElement::ReadNode(const DOMNode* node)
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
			else if( Is_v_NodeName( currentNode ) )
			{
				ValueElement* elemValue = new ValueElement();

				elemValue->ReadNode( currentNode );
				vecElemValue.push_back( elemValue );
			}
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}


bool CombinerElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( attrCount == (unsigned int)-1 ) { str += L"count属性が存在しません\n"; }

	if( vecElemInput.size() < 2 ) { str += L"<input>要素が2つ以上存在しません\n"; }
	if( vecElemValue.empty() ) { str +=L"<v>要素が存在しません\n"; }

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<combiner>\n" + str;
	}

	return str.empty();
}


void CombinerElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return; }

	SetUIntValue( attrCount, Get_count_Attribute( attr ) );
}

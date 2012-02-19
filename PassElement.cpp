#include "stdafx.h"

#include "PassElement.h"



PassElement::PassElement()
{
	elemProgram = NULL;
}


PassElement::~PassElement()
{
	SAFE_DELETE(elemProgram);

	ClearVector( vecElemParam );
	ClearVector( vecElemInput );
}



void PassElement::ReadNode(const DOMNode* node)
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
			if( Is_param_NodeName( currentNode ) )
			{
				ParamElement* elemParam = new ParamElement();
				
				elemParam->ReadNode( currentNode );
				vecElemParam.push_back( elemParam );
			}
			else if( Is_input_NodeName( currentNode ) )
			{
				InputElement* elemInput = new InputElement();

				elemInput->ReadNode( currentNode );
				vecElemInput.push_back( elemInput );
			}
			else if( Is_program_NodeName( currentNode ) )
			{
				_ASSERTE(elemProgram == NULL);		// 0または1つ存在するのでこの時点ではNULL
				elemProgram = new ProgramElement();

				elemProgram->ReadNode( currentNode );
			}
		}

		currentNode = currentNode->getNextSibling();	// 次の要素を処理する
	}
}



bool PassElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( elemProgram != NULL ) { elemProgram->ValidElements( str ); }

	ValidElementsInContainer( vecElemParam, str );
	ValidElementsInContainer( vecElemInput, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<pass>\n" + str;
	}

	return str.empty();
}
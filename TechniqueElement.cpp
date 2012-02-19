#include "stdafx.h"

#include "OpticsElement.h"
#include "TechniqueElement.h"



TechniqueElement::TechniqueElement()
{
	elemAsset = NULL;
	elemCombiner = NULL;
	elemJoints = NULL;
	elemOptics = NULL;
	elemImager = NULL;
	elemProgram = NULL;
}


TechniqueElement::~TechniqueElement()
{
	SAFE_DELETE(elemAsset);
	SAFE_DELETE(elemCombiner);
	SAFE_DELETE(elemJoints);
	SAFE_DELETE(elemOptics);
	SAFE_DELETE(elemImager);
	SAFE_DELETE(elemProgram);

	ClearVector( vecElemAccessor );
	ClearVector( vecElemInput );
	ClearVector( vecElemParam );
	ClearVector( vecElemPass );
}



void TechniqueElement::ReadNode(const DOMNode* node)
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
			if( Is_asset_NodeName( currentNode ) )
			{
				_ASSERTE(elemAsset == NULL);		// 0または1つ存在するのでこの時点ではNULL
				elemAsset = new AssetElement();

				elemAsset->ReadNode( currentNode );
			}
			else if( Is_accessor_NodeName( currentNode ) )
			{
				AccessorElement* elemAccessor = new AccessorElement();
				
				elemAccessor->ReadNode( currentNode );
				vecElemAccessor.push_back( elemAccessor );
			}
			else if( Is_combiner_NodeName( currentNode ) )
			{
				_ASSERTE(elemCombiner == NULL);		// 0または1つ存在するのでこの時点ではNULL

				elemCombiner = new CombinerElement();
				elemCombiner->ReadNode( currentNode );
			}
			else if( Is_joints_NodeName( currentNode ) )
			{
				_ASSERTE(elemJoints == NULL);		// 0または1つ存在するのでこの時点ではNULL

				elemJoints = new JointsElement();
				elemJoints->ReadNode( currentNode );
			}
			else if( Is_optics_NodeName( currentNode ) )
			{
				_ASSERTE(elemOptics == NULL);		// 必ず1つ存在するのでこの時点ではNULL

				elemOptics = new OpticsElement();
				elemOptics->ReadNode( currentNode );
			}
			else if( Is_imager_NodeName( currentNode ) )
			{
				_ASSERTE(elemImager == NULL);		// 0または1つ存在するのでこの時点ではNULL

				elemImager = new ImagerElement();
				elemImager->ReadNode( currentNode );
			}
			else if( Is_input_NodeName( currentNode ) )
			{
				InputElement* elemInput = new InputElement();

				elemInput->ReadNode( currentNode );
				vecElemInput.push_back( elemInput );
			}
			else if( Is_param_NodeName( currentNode ) )
			{
				ParamElement* elemParam = new ParamElement();
				
				elemParam->ReadNode( currentNode );
				vecElemParam.push_back( elemParam );
			}
			else if( Is_pass_NodeName( currentNode ) )
			{
                PassElement* elemPass = new PassElement();

				elemPass->ReadNode( currentNode );
				vecElemPass.push_back( elemPass );
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


bool TechniqueElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( attrProfile.empty() ) { str += L"profile属性が存在しません\n"; }

	if( elemAsset != NULL ) { elemAsset->ValidElements( str ); }
	if( elemCombiner != NULL ) { elemCombiner->ValidElements( str ); }
	if( elemJoints != NULL ) { elemJoints->ValidElements( str ); }
	if( elemOptics != NULL ) { elemOptics->ValidElements( str ); }
	if( elemImager != NULL ) { elemImager->ValidElements( str ); }
	if( elemProgram != NULL ) { elemProgram->ValidElements( str ); }

	ValidElementsInContainer( vecElemAccessor, str );
	ValidElementsInContainer( vecElemInput, str );
	ValidElementsInContainer( vecElemParam, str );
	ValidElementsInContainer( vecElemPass, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<technique>\n" + str;
	}

	return str.empty();
}




void TechniqueElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return ; }

	SetStringValue( attrProfile, Get_profile_Attribute( attr ) );
}
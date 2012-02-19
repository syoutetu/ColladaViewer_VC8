#include "stdafx.h"

#include "AnimationElement.h"



AnimationElement::AnimationElement()
{
}


AnimationElement::~AnimationElement()
{
	ClearVector( vecElemSource );
	ClearVector( vecElemSampler );
	ClearVector( vecElemChannel );
}



void AnimationElement::ReadNode(const DOMNode* node)
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
			else if( Is_sampler_NodeName( currentNode ) )
			{
				SamplerElement* elemSampler = new SamplerElement();

				elemSampler->ReadNode( currentNode );
				vecElemSampler.push_back( elemSampler );
			}
			else if( Is_channel_NodeName( currentNode ) )
			{
				ChannelElement* elemChannel = new ChannelElement();

				elemChannel->ReadNode( currentNode );
				vecElemChannel.push_back( elemChannel );
			}
		}

		currentNode = currentNode->getNextSibling();	// ���̗v�f����������
	}
}



bool AnimationElement::ValidElements(std::wstring& message) const
{
	std::wstring str;

	if( vecElemSource.empty() ) { str += L"<source>�v�f�����݂��܂���\n"; }
	if( vecElemSampler.empty() ) { str += L"<sampler>�v�f�����݂��܂���\n"; }
	if( vecElemChannel.empty() ) { str += L"<channel>�v�f�����݂��܂���\n"; }

	ValidElementsInContainer( vecElemSource, str );
	ValidElementsInContainer( vecElemSampler, str );
	ValidElementsInContainer( vecElemChannel, str );

	if( str.empty() == false )
	{
		InsertTabEachLine( str );
		message += L"<animation>\n" + str;
	}

	return str.empty();
}


void AnimationElement::ReadAttributes(const DOMNode* node)
{
	_ASSERTE(node != NULL);

	DOMNamedNodeMap* attr = node->getAttributes();
	if( attr == NULL ) { return ; }

	SetStringValue( attrId, Get_id_Attribute( attr ) );
	SetStringValue( attrName, Get_name_Attribute( attr ) );
}


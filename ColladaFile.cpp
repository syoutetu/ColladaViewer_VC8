#include "stdafx.h"

#include "DomErrorReporter.h"
#include "ColladaFile.h"



ColladaFile::ColladaFile()
{
	colladaObject = NULL;
}


ColladaFile::~ColladaFile()
{
	SAFE_DELETE(colladaObject);
}



void ColladaFile::CreateColladaObject(const DOMNode* rootNode)
{
	_ASSERTE(rootNode != NULL);
	_ASSERTE(colladaObject == NULL);

	colladaObject = new ColladaObject();

	colladaObject->ReadRootNode( rootNode );
}


bool ColladaFile::Load(LPCWSTR lpszFileName)
{
	if( PathFileExists( lpszFileName ) == FALSE )
	{
		std::wstring strMessage;
		strMessage = strMessage + L"Collada�t�@�C��[" + lpszFileName + L"]��������܂���ł���";
		MessageBox( NULL, strMessage.c_str(), L"ColladaFile::Load()", MB_OK | MB_ICONERROR );
		return false;
	}

	XercesDOMParser* domParser = new XercesDOMParser();

	domParser->setValidationScheme( AbstractDOMParser::Val_Auto );	// �\��������ȏꍇ�ɂ̂ݕ񍐂���
    domParser->setDoNamespaces( false );							// ���O��ԏ����͂��Ȃ�
    domParser->setDoSchema( false );								// �X�L�[�}�����͂��Ȃ�
    domParser->setValidationSchemaFullChecking( false );			// ���S�ȍ\���̃`�F�b�N�͂��Ȃ�

	DomErrorReporter* errorHandler = new DomErrorReporter();
	domParser->setErrorHandler( errorHandler );

	bool bException = false;
	try
	{
		domParser->parse( (const XMLCh*)lpszFileName );
	}
	catch( const OutOfMemoryException& )
	{
		MessageBox( NULL, L"XML�t�@�C�����������Ƀ��������s�����܂���", L"ColladaFile::Load()-OutOfMemoryException", MB_OK | MB_ICONERROR );
		bException = false;
	}
	catch( const XMLException& ex )
	{
		std::wstring strMessage = L"XML�t�@�C�����������ɃG���[���������܂���\n\n";
		strMessage += (const wchar_t*)ex.getMessage();
		MessageBox( NULL, strMessage.c_str(), L"ColladaFile::Load()-XMLException", MB_OK | MB_ICONERROR );
		bException = false;
	}
	catch( const DOMException& ex )
	{
		std::wstring strMessage = L"XML�t�@�C�����������ɃG���[���������܂���\n\n";
		XMLCh temp[2048];
		DOMImplementation::loadDOMExceptionMsg( ex.code, temp, 2047 );
		strMessage += StrX( temp ).getStr();
		MessageBox( NULL, strMessage.c_str(), L"ColladaFile::Load()-DOMException", MB_OK | MB_ICONERROR );
		bException = false;
	}
	catch( ... )
	{
		MessageBox( NULL, L"XML�t�@�C�����������ɃG���[���������܂���", L"ColladaFile::Load()", MB_OK | MB_ICONERROR );
		bException = false;
	}

	bool bError = bException || errorHandler->HasError();
	if( bError == false )	// �G���[���������Ȃ������ꍇ�̓h�L�������g����������
	{
		CreateColladaObject( dynamic_cast<DOMNode*>(domParser->getDocument()) );
		
		if( colladaObject->ValidElements() == false )
		{
			std::wstring strMessage = L"�ǂݍ��܂ꂽCOLLADA�t�@�C�����s���S�ł�\n\n";
			strMessage += colladaObject->GetErrorMessage();
			MessageBox( NULL, strMessage.c_str(), L"COLLADA�t�@�C���̓ǂݍ���", MB_OK | MB_ICONWARNING );
			bError = true;
		}
	}
	else
	{
		std::wstring strMessage;
		if( errorHandler->GetFatalErrorMessage().empty() == false )
		{
			strMessage += L"�v���I�ȃG���[\n";
			strMessage += errorHandler->GetFatalErrorMessage();
		}

		if( errorHandler->GetErrorMessage().empty() == false )
		{
			strMessage += L"�G���[\n";
			strMessage += errorHandler->GetErrorMessage();
		}

		if( strMessage.empty() == false )	// �G���[���b�Z�[�W������ꍇ�͕\������
		{
			MessageBox( NULL, strMessage.c_str(), L"ColladaFile::Load()", MB_OK | MB_ICONERROR );
		}
	}

	delete errorHandler;
	delete domParser;

	return bError == false;
}
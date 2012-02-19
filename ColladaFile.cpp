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
		strMessage = strMessage + L"Colladaファイル[" + lpszFileName + L"]が見つかりませんでした";
		MessageBox( NULL, strMessage.c_str(), L"ColladaFile::Load()", MB_OK | MB_ICONERROR );
		return false;
	}

	XercesDOMParser* domParser = new XercesDOMParser();

	domParser->setValidationScheme( AbstractDOMParser::Val_Auto );	// 構文が特殊な場合にのみ報告する
    domParser->setDoNamespaces( false );							// 名前空間処理はしない
    domParser->setDoSchema( false );								// スキーマ処理はしない
    domParser->setValidationSchemaFullChecking( false );			// 完全な構文のチェックはしない

	DomErrorReporter* errorHandler = new DomErrorReporter();
	domParser->setErrorHandler( errorHandler );

	bool bException = false;
	try
	{
		domParser->parse( (const XMLCh*)lpszFileName );
	}
	catch( const OutOfMemoryException& )
	{
		MessageBox( NULL, L"XMLファイルを処理中にメモリが不足しました", L"ColladaFile::Load()-OutOfMemoryException", MB_OK | MB_ICONERROR );
		bException = false;
	}
	catch( const XMLException& ex )
	{
		std::wstring strMessage = L"XMLファイルを処理中にエラーが発生しました\n\n";
		strMessage += (const wchar_t*)ex.getMessage();
		MessageBox( NULL, strMessage.c_str(), L"ColladaFile::Load()-XMLException", MB_OK | MB_ICONERROR );
		bException = false;
	}
	catch( const DOMException& ex )
	{
		std::wstring strMessage = L"XMLファイルを処理中にエラーが発生しました\n\n";
		XMLCh temp[2048];
		DOMImplementation::loadDOMExceptionMsg( ex.code, temp, 2047 );
		strMessage += StrX( temp ).getStr();
		MessageBox( NULL, strMessage.c_str(), L"ColladaFile::Load()-DOMException", MB_OK | MB_ICONERROR );
		bException = false;
	}
	catch( ... )
	{
		MessageBox( NULL, L"XMLファイルを処理中にエラーが発生しました", L"ColladaFile::Load()", MB_OK | MB_ICONERROR );
		bException = false;
	}

	bool bError = bException || errorHandler->HasError();
	if( bError == false )	// エラーが発生しなかった場合はドキュメントを処理する
	{
		CreateColladaObject( dynamic_cast<DOMNode*>(domParser->getDocument()) );
		
		if( colladaObject->ValidElements() == false )
		{
			std::wstring strMessage = L"読み込まれたCOLLADAファイルが不完全です\n\n";
			strMessage += colladaObject->GetErrorMessage();
			MessageBox( NULL, strMessage.c_str(), L"COLLADAファイルの読み込み", MB_OK | MB_ICONWARNING );
			bError = true;
		}
	}
	else
	{
		std::wstring strMessage;
		if( errorHandler->GetFatalErrorMessage().empty() == false )
		{
			strMessage += L"致命的なエラー\n";
			strMessage += errorHandler->GetFatalErrorMessage();
		}

		if( errorHandler->GetErrorMessage().empty() == false )
		{
			strMessage += L"エラー\n";
			strMessage += errorHandler->GetErrorMessage();
		}

		if( strMessage.empty() == false )	// エラーメッセージがある場合は表示する
		{
			MessageBox( NULL, strMessage.c_str(), L"ColladaFile::Load()", MB_OK | MB_ICONERROR );
		}
	}

	delete errorHandler;
	delete domParser;

	return bError == false;
}
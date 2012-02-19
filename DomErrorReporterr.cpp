#include "stdafx.h"

#include "DomErrorReporter.h"


// ---------------------------------------------------------------------------
//  ErrorHandler インターフェイスの実装
// ---------------------------------------------------------------------------
void DomErrorReporter::error(const SAXParseException& ex)
{
	ErrorFormat( strErrorMessage, ex );
}

void DomErrorReporter::fatalError(const SAXParseException& ex)
{
	ErrorFormat( strFatalErrorMessage, ex );
}

void DomErrorReporter::warning(const SAXParseException& ex)
{
	ErrorFormat( strWarningMessage, ex );
}

void DomErrorReporter::resetErrors()
{
	strErrorMessage.clear();
	strFatalErrorMessage.clear();
	strWarningMessage.clear();
}


// メッセージを形成してstrMessageに追加する
void DomErrorReporter::ErrorFormat(std::wstring& strMessage, const SAXParseException& ex)
{
	StrX line( ex.getLineNumber() );
	StrX column( ex.getColumnNumber() );
	StrX message( ex.getMessage() );

	strMessage += L"(line:" + line.getStr() + L", column:" + column.getStr() + L") message: " + message.getStr() + L"\n";
}

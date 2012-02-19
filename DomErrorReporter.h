
#pragma once

#if !defined ___DomErrorReporter_h___
#define ___DomErrorReporter_h___



class DomErrorReporter: public ErrorHandler
{

public:

    // -----------------------------------------------------------------------
    //  ErrorHandler インターフェイスの実装
    // -----------------------------------------------------------------------
    void warning(const SAXParseException& ex);
    void error(const SAXParseException& ex);
    void fatalError(const SAXParseException& ex);
	void resetErrors();

public:

	DomErrorReporter()	{}
	~DomErrorReporter()	{}


	bool HasError() const	{ return strErrorMessage.empty() == false || strFatalErrorMessage.empty() == false; }
	bool HasWarning() const	{ return strWarningMessage.empty() == false; }

	const std::wstring&	GetWarningMessage() const		{ return strWarningMessage; }
	const std::wstring&	GetErrorMessage() const			{ return strErrorMessage; }
	const std::wstring&	GetFatalErrorMessage() const	{ return strFatalErrorMessage; }

private:

	std::wstring		strWarningMessage;			// 警告メッセージ
	std::wstring		strErrorMessage;			// エラーメッセージ
	std::wstring		strFatalErrorMessage;		// 致命的なエラーメッセージ


	void ErrorFormat(std::wstring& strMessage, const SAXParseException& ex);

};



// ---------------------------------------------------------------------------
//  XMLCh型をローカルな型に変換するクラス(VC++でwchar_tを想定しているので変換しない)
// ---------------------------------------------------------------------------
class StrX
{
public :

    StrX(const XMLCh* const toTranscode)	{ fLocalForm = (const wchar_t*)toTranscode; }
	StrX(const XMLSSize_t toTranscode)
	{
		XMLCh tmpChar[32];
		XMLString::binToText( toTranscode, tmpChar, 31, 10 );
		tmpChar[31] = chNull;	// 安全の為閉じておく
		fLocalForm = (const wchar_t*)tmpChar;
	}

    ~StrX()	{}

	const std::wstring& getStr() const	{ return fLocalForm; }

private :

	std::wstring   fLocalForm;
};

// ostreamにStrXを出力する
inline std::ostream& operator<<(std::ostream& target, const StrX& toDump)
{
    target << toDump.getStr().c_str();
    return target;
}


#endif	//___DomErrorReporter_h___
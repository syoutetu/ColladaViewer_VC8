
#pragma once

#if !defined ___ColladaSaxHandler_h___
#define ___ColladaSaxHandler_h___

XERCES_CPP_NAMESPACE_USE

class CColladaSaxHandler: public DefaultHandler, private XMLFormatTarget
{
public:

    // -----------------------------------------------------------------------
    //  XMLFormatTarget インターフェイスの実装
    // -----------------------------------------------------------------------
    void writeChars(const XMLByte* const toWrite, const unsigned int count, XMLFormatter* const formatter);

    // -----------------------------------------------------------------------
    //  DocumentHandler インターフェイスの実装
    // -----------------------------------------------------------------------
    void endDocument();
    void endElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
    void characters(const XMLCh* const chars, const unsigned int length);
    void ignorableWhitespace(const XMLCh* const chars, const unsigned int length);
    void processingInstruction(const XMLCh* const target, const XMLCh* const data);
    void startDocument();
    void startElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attributes);


    // -----------------------------------------------------------------------
    //  ErrorHandler インターフェイスの実装
    // -----------------------------------------------------------------------
    void warning(const SAXParseException& ex);
    void error(const SAXParseException& ex);
    void fatalError(const SAXParseException& ex);


    // -----------------------------------------------------------------------
    //  DTDHandler インターフェイスの実装
    // -----------------------------------------------------------------------
    void notationDecl(const XMLCh* const name, const XMLCh* const publicId, const XMLCh* const systemId);
    void unparsedEntityDecl(const XMLCh* const name, const XMLCh* const publicId, const XMLCh* const systemId, const XMLCh* const notationName);


private:

    XMLFormatter    fFormatter;		// データ出力の為のフォーマッタオブジェクト

	std::wstring		strWarningMessage;			// 警告メッセージ
	std::wstring		strErrorMessage;			// エラーメッセージ
	std::wstring		strFatalErrorMessage;		// 致命的なエラーメッセージ


	void ErrorFormat(std::wstring& strMessage, const SAXParseException& ex);

public:

    CColladaSaxHandler(const char* const encodingName);
    ~CColladaSaxHandler();

	const std::wstring&	GetWarningMessage() const		{ return strWarningMessage; }
	const std::wstring&	GetErrorMessage() const			{ return strErrorMessage; }
	const std::wstring&	GetFatalErrorMessage() const	{ return strFatalErrorMessage; }
};



// ---------------------------------------------------------------------------
//  XMLCh型をローカルな型に変換するクラス(VC++でwchar_tを想定しているので変換しない)
// ---------------------------------------------------------------------------
class StrX
{
public :

    StrX(const XMLCh* const toTranscode)	{ fLocalForm = toTranscode; }
	StrX(const XMLSSize_t toTranscode)
	{
		XMLCh tmpChar[32];
		XMLString::binToText( toTranscode, tmpChar, 31, 10 );
		tmpChar[31] = chNull;	// 安全の為閉じておく
		fLocalForm = tmpChar;
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


#endif	//___ColladaSaxHandler_h___
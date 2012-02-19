#include "stdafx.h"

#include "ColladaSaxHandler.h"


// ---------------------------------------------------------------------------
//  固定の文字列を定義
// ---------------------------------------------------------------------------
static const XMLCh  gEndElement[] = { chOpenAngle, chForwardSlash, chNull };
static const XMLCh  gEndPI[] = { chQuestion, chCloseAngle, chNull };
static const XMLCh  gStartPI[] = { chOpenAngle, chQuestion, chNull };
static const XMLCh  gXMLDecl1[] =
{
        chOpenAngle, chQuestion, chLatin_x, chLatin_m, chLatin_l
    ,   chSpace, chLatin_v, chLatin_e, chLatin_r, chLatin_s, chLatin_i
    ,   chLatin_o, chLatin_n, chEqual, chDoubleQuote, chDigit_1, chPeriod
    ,   chDigit_0, chDoubleQuote, chSpace, chLatin_e, chLatin_n, chLatin_c
    ,   chLatin_o, chLatin_d, chLatin_i, chLatin_n, chLatin_g, chEqual
    ,   chDoubleQuote, chNull
};
static const XMLCh  gXMLDecl2[] =
{
        chDoubleQuote, chQuestion, chCloseAngle
    ,   chLF, chNull
};



// ---------------------------------------------------------------------------
//  コンストラクタとデストラクタ
// ---------------------------------------------------------------------------
CColladaSaxHandler::CColladaSaxHandler(const char* const encodingName):
					fFormatter(encodingName, 0, this, XMLFormatter::NoEscapes, XMLFormatter::UnRep_CharRef)
{
    // XML宣言を出力する
    fFormatter << gXMLDecl1 << fFormatter.getEncodingName() << gXMLDecl2;
}

CColladaSaxHandler::~CColladaSaxHandler()
{
}


// ---------------------------------------------------------------------------
//  XMLFormatTarget インターフェイスの実装
// ---------------------------------------------------------------------------
void CColladaSaxHandler::writeChars(const XMLByte* const toWrite, const unsigned int count, XMLFormatter* const formatter)
{
    // For this one, just dump them to the standard output
    // Surprisingly, Solaris was the only platform on which
    // required the char* cast to print out the string correctly.
    // Without the cast, it was printing the pointer value in hex.
    // Quite annoying, considering every other platform printed
    // the string with the explicit cast to char* below.
  XERCES_STD_QUALIFIER cout.write((char *) toWrite, (int) count);
	XERCES_STD_QUALIFIER cout.flush();
}


// ---------------------------------------------------------------------------
//  ErrorHandler インターフェイスの実装
// ---------------------------------------------------------------------------
void CColladaSaxHandler::error(const SAXParseException& ex)
{
	ErrorFormat( strErrorMessage, ex );
}

void CColladaSaxHandler::fatalError(const SAXParseException& ex)
{
	ErrorFormat( strFatalErrorMessage, ex );
}

void CColladaSaxHandler::warning(const SAXParseException& ex)
{
	ErrorFormat( strWarningMessage, ex );
}


// メッセージを形成してstrMessageに追加する
void CColladaSaxHandler::ErrorFormat(std::wstring& strMessage, const SAXParseException& ex)
{
	StrX line( ex.getLineNumber() );
	StrX column( ex.getColumnNumber() );
	StrX message( ex.getMessage() );

	strMessage += L"(line:" + line.getStr() + L", column:" + column.getStr() + L") message: " + message.getStr() + L"\n";
}


// ---------------------------------------------------------------------------
//  DTDHandler インターフェイスの実装
// ---------------------------------------------------------------------------
void CColladaSaxHandler::unparsedEntityDecl(const XMLCh* const name, const XMLCh* const publicId, const XMLCh* const systemId,
											const XMLCh* const notationName)
{
    // Not used at this time
}


void CColladaSaxHandler::notationDecl(const XMLCh* const name, const XMLCh* const publicId, const XMLCh* const systemId)
{
    // Not used at this time
}


// ---------------------------------------------------------------------------
//  DocumentHandler インターフェイスの実装
// ---------------------------------------------------------------------------
void CColladaSaxHandler::characters(const XMLCh* const chars, const unsigned int length)
{
    fFormatter.formatBuf(chars, length, XMLFormatter::CharEscapes);
}


void CColladaSaxHandler::endDocument()
{
	int i = 0;
}


void CColladaSaxHandler::endElement(const XMLCh* const uri, const XMLCh* const localname,const XMLCh* const qname)
{
    // No escapes are legal here
    fFormatter << XMLFormatter::NoEscapes << gEndElement ;

	fFormatter << qname << chCloseAngle;
}


void CColladaSaxHandler::ignorableWhitespace(const XMLCh* const chars,const  unsigned int length)
{
    fFormatter.formatBuf(chars, length, XMLFormatter::NoEscapes);
}


void CColladaSaxHandler::processingInstruction(const XMLCh* const target, const XMLCh* const data)
{
    fFormatter << XMLFormatter::NoEscapes << gStartPI  << target;
    if (data)
        fFormatter << chSpace << data;
    fFormatter << XMLFormatter::NoEscapes << gEndPI;
}


void CColladaSaxHandler::startDocument()
{
	int i = 0;
}


void CColladaSaxHandler::startElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname,
									  const Attributes& attributes)
{
    // The name has to be representable without any escapes
    fFormatter  << XMLFormatter::NoEscapes << chOpenAngle ;

	fFormatter << qname ;

    unsigned int len = attributes.getLength();
    for (unsigned int index = 0; index < len; index++)
    {
        //
        //  Again the name has to be completely representable. But the
        //  attribute can have refs and requires the attribute style
        //  escaping.
        //
        fFormatter  << XMLFormatter::NoEscapes << chSpace ;
		fFormatter  << attributes.getQName(index) ;

		fFormatter  << chEqual << chDoubleQuote
                    << XMLFormatter::AttrEscapes
		            << attributes.getValue(index)
                    << XMLFormatter::NoEscapes
                    << chDoubleQuote;
    }
    fFormatter << chCloseAngle;
}

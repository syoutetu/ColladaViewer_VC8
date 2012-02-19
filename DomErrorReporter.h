
#pragma once

#if !defined ___DomErrorReporter_h___
#define ___DomErrorReporter_h___



class DomErrorReporter: public ErrorHandler
{

public:

    // -----------------------------------------------------------------------
    //  ErrorHandler �C���^�[�t�F�C�X�̎���
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

	std::wstring		strWarningMessage;			// �x�����b�Z�[�W
	std::wstring		strErrorMessage;			// �G���[���b�Z�[�W
	std::wstring		strFatalErrorMessage;		// �v���I�ȃG���[���b�Z�[�W


	void ErrorFormat(std::wstring& strMessage, const SAXParseException& ex);

};



// ---------------------------------------------------------------------------
//  XMLCh�^�����[�J���Ȍ^�ɕϊ�����N���X(VC++��wchar_t��z�肵�Ă���̂ŕϊ����Ȃ�)
// ---------------------------------------------------------------------------
class StrX
{
public :

    StrX(const XMLCh* const toTranscode)	{ fLocalForm = (const wchar_t*)toTranscode; }
	StrX(const XMLSSize_t toTranscode)
	{
		XMLCh tmpChar[32];
		XMLString::binToText( toTranscode, tmpChar, 31, 10 );
		tmpChar[31] = chNull;	// ���S�̈ו��Ă���
		fLocalForm = (const wchar_t*)tmpChar;
	}

    ~StrX()	{}

	const std::wstring& getStr() const	{ return fLocalForm; }

private :

	std::wstring   fLocalForm;
};

// ostream��StrX���o�͂���
inline std::ostream& operator<<(std::ostream& target, const StrX& toDump)
{
    target << toDump.getStr().c_str();
    return target;
}


#endif	//___DomErrorReporter_h___
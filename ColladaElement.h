
#pragma once

#if !defined ___ColladaElement_h___
#define ___ColladaElement_h___


#include<string>


// <COLLADA>�G�������g�̏���ۑ�����N���X
class ColladaElement
{

public:

	const std::wstring& GetVersion() const	{ return version; }
	const std::wstring& GetXmlNameSpace() const	{ return xmlns; }

	ColladaElement()
	{
		// �Ƃ肠�����Œ��:
		version = L"1.3.0";
		xmlns = L"http://www.collada.org/2005/COLLADASchema";
	}

private:
	
	//====================================
	// �A�g���r���[�g
	//====================================
	std::wstring	version;
	std::wstring	xmlns;
};



#endif	//___ColladaElement_h___
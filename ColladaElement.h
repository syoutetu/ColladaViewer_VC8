
#pragma once

#if !defined ___ColladaElement_h___
#define ___ColladaElement_h___


#include<string>


// <COLLADA>エレメントの情報を保存するクラス
class ColladaElement
{

public:

	const std::wstring& GetVersion() const	{ return version; }
	const std::wstring& GetXmlNameSpace() const	{ return xmlns; }

	ColladaElement()
	{
		// とりあえず固定に:
		version = L"1.3.0";
		xmlns = L"http://www.collada.org/2005/COLLADASchema";
	}

private:
	
	//====================================
	// アトリビュート
	//====================================
	std::wstring	version;
	std::wstring	xmlns;
};



#endif	//___ColladaElement_h___
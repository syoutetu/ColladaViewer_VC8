
#pragma once

#if !defined ___ColladaAttributeName_h___
#define ___ColladaAttributeName_h___


static const XMLCh* EMPTY_STRING = (XMLCh*)L"";


// ノードの属性の値を取得するマクロ
// 属性が見つからなかった場合は空の文字列を返す
#define GET_ATTR(c)															\
	inline const XMLCh* Get_##c##_Attribute(const DOMNamedNodeMap* attr)	\
	{																		\
		DOMNode* item = NULL;												\
																			\
		_ASSERTE(sizeof(XMLCh) == sizeof(wchar_t));							\
		item = attr->getNamedItem( (XMLCh*)L#c );							\
																			\
		if( item == NULL ) { return EMPTY_STRING; }							\
		return item->getNodeValue();										\
	}


GET_ATTR(count)
GET_ATTR(depth)
GET_ATTR(digits)
GET_ATTR(flow)
GET_ATTR(format)
GET_ATTR(function)
GET_ATTR(height)
GET_ATTR(id)
GET_ATTR(idx)
GET_ATTR(lang)
GET_ATTR(magnitude)
GET_ATTR(material)
GET_ATTR(meter)
GET_ATTR(MinInclusive)
GET_ATTR(MaxInclusive)
GET_ATTR(name)
GET_ATTR(offset)
GET_ATTR(profile)
GET_ATTR(semantic)
GET_ATTR(sid)
GET_ATTR(source)
GET_ATTR(stride)
GET_ATTR(target)
GET_ATTR(type)
GET_ATTR(url)
GET_ATTR(width)


#undef GET_ATTR


#endif	//___ColladaAttributeName_h___

#pragma once

#if !defined ___ColladaElementName_h___
#define ___ColladaElementName_h___




// ノードの名前の文字列を比較する関数を生成するマクロ
// 注意: equals()はNULLと空の文字を同じと扱う
#define IS_EQUAL(c)															\
	inline bool Is_##c##_NodeName(const DOMNode* node)						\
	{																		\
		_ASSERTE(node != NULL);												\
		_ASSERTE(sizeof(XMLCh) == sizeof(wchar_t));							\
																			\
		return XMLString::equals( node->getNodeName(), (const XMLCh*)L#c);	\
	}

IS_EQUAL(COLLADA)
IS_EQUAL(scene)
IS_EQUAL(node)
IS_EQUAL(boundingbox)
IS_EQUAL(min)
IS_EQUAL(max)
IS_EQUAL(camera)
IS_EQUAL(optics)
IS_EQUAL(imager)
IS_EQUAL(instance)
IS_EQUAL(library)
IS_EQUAL(animation)
IS_EQUAL(channel)
IS_EQUAL(sampler)
IS_EQUAL(controller)
IS_EQUAL(skin)
IS_EQUAL(combiner)
IS_EQUAL(v)
IS_EQUAL(joints)
IS_EQUAL(geometry)
IS_EQUAL(mesh)
IS_EQUAL(lines)
IS_EQUAL(linestrips)
IS_EQUAL(polygons)
IS_EQUAL(triangles)
IS_EQUAL(trifans)
IS_EQUAL(tristrips)
IS_EQUAL(p)
IS_EQUAL(vertices)
IS_EQUAL(source)
IS_EQUAL(accessor)
IS_EQUAL(array)
IS_EQUAL(bool_array)
IS_EQUAL(float_array)
IS_EQUAL(int_array)
IS_EQUAL(Name_array)
IS_EQUAL(input)
IS_EQUAL(material)
IS_EQUAL(shader)
IS_EQUAL(pass)
IS_EQUAL(technique)
IS_EQUAL(image)
IS_EQUAL(light)
IS_EQUAL(texture)
IS_EQUAL(program)
IS_EQUAL(code)
IS_EQUAL(entry)
IS_EQUAL(param)
IS_EQUAL(matrix)
IS_EQUAL(lookat)
IS_EQUAL(perspective)
IS_EQUAL(rotate)
IS_EQUAL(scale)
IS_EQUAL(skew)
IS_EQUAL(translate)
IS_EQUAL(asset)
IS_EQUAL(extra)
IS_EQUAL(author)
IS_EQUAL(authoring_tool)
IS_EQUAL(created)
IS_EQUAL(modified)
IS_EQUAL(revision)
IS_EQUAL(source_data)
IS_EQUAL(copyright)
IS_EQUAL(title)
IS_EQUAL(subject)
IS_EQUAL(keywords)
IS_EQUAL(comments)
IS_EQUAL(unit)
IS_EQUAL(up_axis)

#undef IS_EQUAL



#endif	//___ColladaElementName_h___
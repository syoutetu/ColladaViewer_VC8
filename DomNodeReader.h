
#pragma once

#if !defined ___DomNodeReader_h___
#define ___DomNodeReader_h___



// DOMノードを読み込むインターフェース
class DomNodeReader
{
public:

	// DOMノードを読み込む
	virtual void ReadNode(const DOMNode* node) = 0;

	// 要素が正常な状態にある(必ず必要な属性が読み込まれた)ことを確認する
	// エラーがある場合はmessageに追加する
	virtual bool ValidElements(std::wstring& message) const = 0;	

protected:

	DomNodeReader()	{}
	virtual ~DomNodeReader()	{}

};



// ====================================
// テンプレート関数
// ====================================

// size()でサイズ、[]でDomNodeReader*が取得できるコンテナ内のValidElements()を処理する
template<typename _Cnt>	
inline void ValidElementsInContainer(_Cnt& cnt, std::wstring& message)
{
	unsigned int size = (unsigned int)cnt.size();
	for( unsigned int i = 0; i < size; i++ ) { cnt[i]->ValidElements( message ); }
}


#endif	//___DomNodeReader_h___
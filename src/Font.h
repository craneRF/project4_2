#pragma once
#include "ofMain.h"

template<typename T> class ResourceManager;  //template付きクラスの前方宣言

class Font
{
public:
	Font();
	~Font();

	inline const unordered_map<string, unordered_map<int, shared_ptr<ofTrueTypeFont>>> GetFontMap(){ return m_FontData; }

private:
	bool Load();

	string m_fontname;  //m_FontDataのキーとなる変数

	unique_ptr< ResourceManager<string>> mp_fontManager;

	const vector<int> m_fontSize = {  //使用するであろうフォントのサイズをあらかじめ用意しておく
		8, 18, 28/*, 38, 48, 58*/
		//フォントサイズを増やすとメモリ不足か何かでエラーが出て起動しない模様
	};

	unordered_map<string, unordered_map<int, shared_ptr<ofTrueTypeFont>>> m_FontData;  //フォントの種類管理マップ
};


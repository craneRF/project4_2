#pragma once
#include "ofMain.h"

class ItemManager
{
public:
	ItemManager();
	~ItemManager() {};

	// 初期化
	void Initialize();

	//vector<int> _itemlist;
	map<string,int> _itemlist;

	//アイテムリストに追加、val分増やす
	void setItem(int itemtype, int val);

	//アイテムリストを参照し減らす、無くなったら消す
	void eraseItem(int itemtype);

	//アイテムの個数を返す
	int getItemNum(int itemtype);

	//アイテムが存在するかをboolで返す
	bool isItem(int itemtype);

	//アイテムリストを表示
	string DisplayItemList();
private:

};
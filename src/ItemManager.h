#pragma once
#include "ofMain.h"

class ItemManager
{
public:
	ItemManager();
	~ItemManager() {};

	// ������
	void Initialize();

	//vector<int> _itemlist;
	map<string,int> _itemlist;

	//�A�C�e�����X�g�ɒǉ��Aval�����₷
	void setItem(int itemtype, int val);

	//�A�C�e�����X�g���Q�Ƃ����炷�A�����Ȃ��������
	void eraseItem(int itemtype);

	//�A�C�e���̌���Ԃ�
	int getItemNum(int itemtype);

	//�A�C�e�������݂��邩��bool�ŕԂ�
	bool isItem(int itemtype);

	//�A�C�e�����X�g��\��
	string DisplayItemList();
private:

};
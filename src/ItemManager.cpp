#include "ItemManager.h"
#include "ItemType.h"
#include "ItemComponent.h"

ItemManager::ItemManager() {
	setItem(ItemType::POTION, 3);
	setItem(ItemType::ATKUp, 1);
}

void ItemManager::setItem(int itemtype, int val) {
	_itemlist[ItemComponent::getItemName(itemtype)] += val;
}

void ItemManager::eraseItem(int itemtype) {
	auto it = _itemlist.find(ItemComponent::getItemName(itemtype));
	if (_itemlist.end() == it || it->second - 1 == 0) {
		_itemlist.erase(it);
	}
	else {
		it->second -= 1;
	}
}

int ItemManager::getItemNum(int itemtype) {
	auto it = _itemlist.find(ItemComponent::getItemName(itemtype));
	if (_itemlist.end() == it) {
		return NULL;
	}
	else {
		return it->second;
	}
}

bool ItemManager::isItem(int itemtype)
{
	auto it = _itemlist.find(ItemComponent::getItemName(itemtype));
	if (_itemlist.end() == it) {
		return false;
	}
	else {
		return true;
	}
}

string ItemManager::DisplayItemList() {
	string litemlistText;
	for (auto& ilist : _itemlist) {
		litemlistText += ilist.first + u8"Å@" + ofToString(ilist.second) + "\n";
	}
	return litemlistText;
}



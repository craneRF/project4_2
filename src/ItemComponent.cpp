#include "ItemComponent.h"
#include "SpriteComponent.h"
#include "ItemObject.h"
#include "ItemType.h"

Potion ItemComponent::m_potion;
HiPower ItemComponent::m_hiopower;

void ItemComponent::useItem(int itemtype) {
	if (ofApp::getInstance()->mp_itemManager->isItem(itemtype)) {
		getItem(itemtype).m_iParam.itemEffect();
		cout << getItem(itemtype).m_iParam.itemText << "\n";
		ofApp::getInstance()->mp_itemManager->eraseItem(itemtype);
	}
	else {
		cout << "ƒAƒCƒeƒ€‚ª‚ ‚è‚Ü‚¹‚ñ\n";
	}
}

ItemObject ItemComponent::getItem(int itemtype) {
	switch (itemtype) {
	case ItemType::POTION:
		return m_potion;
	case ItemType::ATKUp:
		return m_hiopower;
	default:
		break;
	}
}

string ItemComponent::getItemName(int itemtype)
{
	return getItem(itemtype).m_iParam.itemName;
}

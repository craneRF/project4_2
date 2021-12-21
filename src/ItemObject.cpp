#include "ItemObject.h"
#include "Effect.h"

Potion::Potion() {
	m_iParam.itemName = u8"ポーション";
	m_iParam.itemText = "HPを20回復する";
	m_iParam.itemEffect = [=]() {
		Effect::healHP(20);
	};
}

HiPower::HiPower(){
	m_iParam.itemName = u8"ハイパワー";
	m_iParam.itemText = "攻撃力の基礎値を1上昇する";
	m_iParam.itemEffect = [=]() {
		Effect::increaseATK(1);
	};
}

#include "ItemObject.h"
#include "Effect.h"

Potion::Potion() {
	m_iParam.itemName = u8"�|�[�V����";
	m_iParam.itemText = "HP��20�񕜂���";
	m_iParam.itemEffect = [=]() {
		Effect::healHP(20);
	};
}

HiPower::HiPower(){
	m_iParam.itemName = u8"�n�C�p���[";
	m_iParam.itemText = "�U���͂̊�b�l��1�㏸����";
	m_iParam.itemEffect = [=]() {
		Effect::increaseATK(1);
	};
}

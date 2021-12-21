#pragma once
#include "ofMain.h"
#include "Effect.h"

struct ItemParam {
	string itemName;
	string itemImageName;
	string itemText;
	function<void()> itemEffect;
};

class ItemObject
{
public:
	ItemObject() {};
	virtual ~ItemObject() {};

	virtual void initialize() {};
	ItemParam m_iParam;
protected:
	Effect m_effect;
};

class Potion :public ItemObject
{
public:
	Potion();
};

class HiPower :public ItemObject
{
public:
	HiPower();
};
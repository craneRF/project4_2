#pragma once
#include "ofApp.h"
#include "ItemObject.h"

class SpriteComponent;

class ItemComponent :public Component
{
public:
	ItemComponent(GameActor* _gactor) :Component(_gactor, "ItemComponent") {};
	virtual ~ItemComponent() {};
	virtual void update() {};
	virtual void input() {};

	void useItem(int itemtype);
	
	static ItemObject getItem(int itemtype);
	static string getItemName(int itemtype);
private:
	static Potion m_potion;
	static HiPower m_hiopower;
	SpriteComponent * mp_sprCpnt;
};


#include "BattleHUD.h"
#include "UISprite.h"

BattleHUD::BattleHUD()
	:UIScreen("BattleHUD")
{
	uis = addUIActor<UISprite>("Sprite");
	//uis->setParam({ 100.0f, 100.0f, 0.0f }, { 0.75f, 0.75f }, 0.0f);
	uis->initialize("marine_icon.png");
}

BattleHUD::~BattleHUD()
{
}

void BattleHUD::initialize()
{
	/*uis = addUIActor<UISprite>("Sprite");
	uis->setParam({ 100.0f, 100.0f, 0.0f }, { 0.75f, 0.75f }, 0.0f);
	uis->initialize("marine_icon.png");*/
}

void BattleHUD::update(float _deltaTime)
{
}

void BattleHUD::input(float _deltaTime)
{
}

void BattleHUD::draw()
{
	UIScreen::draw();
}

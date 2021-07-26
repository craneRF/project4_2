#include "BattleHUD.h"
#include "UISprite.h"

BattleHUD::BattleHUD()
	:UIPanelCanvas("BattleHUD")
{
	uis = addUICommon<UISprite>("Sprite");
	uis->initialize("marine_icon.png", { 100.0f, 100.0f, 0.0f }, { 0.025f, 0.025f }, 0.0f);
}

BattleHUD::~BattleHUD()
{
}

void BattleHUD::update(float _deltaTime)
{
	UIPanelCanvas::update(_deltaTime);
}

void BattleHUD::input(float _deltaTime)
{
	UIPanelCanvas::input(_deltaTime);
}

void BattleHUD::draw()
{
	UIPanelCanvas::draw();
}

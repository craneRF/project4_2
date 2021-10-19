#include "BattleHUD.h"
#include "UISprite.h"
#include "UIFont.h"

BattleHUD::BattleHUD()
	:UIPanelCanvas("BattleHUD")
{
	uis = addUICommon<UISprite>("Sprite");
	uis->initialize("marine_icon.png", { 100.0f, 100.0f, 0.0f }, { 0.025f, 0.025f }, 0.0f);
	/*uif = addUICommon<UIFont>("Font");
	uif->initialize("BattleHUD", 18, { 150.0f, 150.0f, 0.0f }, ofColor::white, {2.0f, 2.0f, 1.0f});*/
	uis2 = addUICommon<UISprite>("Sprite2");
	uis2->initialize("marine_icon.png", { 150.0f, 150.0f, 0.0f }, { 0.025f,0.025f }, 0.0f);
	//uis2->UIupdatefunc = [=](){ uis2->Pos() = uis2->Pos() + 1.0f; };
	/*uif2 = addUICommon<UIFont>("Font2");
	uif2->initialize("Font", 18, { 150.0f, 150.0f, 0.0f }, ofColor::white, { 2.0f, 2.0f, 1.0f });*/
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

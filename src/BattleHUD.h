#pragma once
#include "UIPanelCanvas.h"

class UISprite;
class UIFont;

class BattleHUD : public UIPanelCanvas
{
public:
	BattleHUD();
	~BattleHUD();

	void update(float _deltaTime) override;
	void input(float _deltaTime) override;
	void draw() override;

public:
	UISprite* uis;
	UISprite* uis2;
	UIFont* uif;
	UIFont* uif2;
};


#pragma once
#include "UIPanelCanvas.h"

class UISprite;
class UIFont;

class BattleHUD : public UIPanelCanvas
{
public:
	BattleHUD();
	~BattleHUD();

	//void update() override;
	//void input() override;
	//void draw() override;

public:
	UISprite* uis;
	UISprite* uis2;
	UIFont* uif;
	UIFont* uif2;
};


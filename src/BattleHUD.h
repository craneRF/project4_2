#pragma once
#include "UIPanelCanvas.h"

class UISprite;

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
};


#pragma once
#include "UIScreen.h"

class UISprite;

class BattleHUD : public UIScreen
{
public:
	BattleHUD();
	~BattleHUD();

	void initialize() override;
	void update(float _deltaTime) override;
	void input(float _deltaTime) override;
	void draw() override;

public:
	UISprite* uis;
};


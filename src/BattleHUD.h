#pragma once
#include "UIScreen.h"

class BattleHUD : public UIScreen
{
	BattleHUD();
	~BattleHUD();

	void initialize();
	void update(float _deltaTime) override;
	void input(float _deltaTime) override;
	void draw(float _deltaTime) override;
};


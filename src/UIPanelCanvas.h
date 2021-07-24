#pragma once
#include "UIPanel.h"

class UIPanelCanvas : public UIPanel
{
public:
	UIPanelCanvas(string _name = "");
	~UIPanelCanvas();

	void update(float _deltatime) override;
	void input(float _deltatime) override;
	void draw() override;
};


#pragma once
#include "UIPanel.h"

class UIPanelCanvas : public UIPanel
{
public:
	UIPanelCanvas(string _name = "");
	~UIPanelCanvas();

	void update() override;
	void input() override;
	void draw() override;
};


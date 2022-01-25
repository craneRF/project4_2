#pragma once
#include "ofMain.h"
#include "Component.h"

class GameActor;
class UIPanelCanvas;

class UIComponent  final : public Component
{
private:

public:
	UIComponent(GameActor* _gactor);
	virtual ~UIComponent();

	virtual void update();
	virtual void input();

	UIPanelCanvas* mp_UICanvasParent;  //自身がどのUIScreenに存在しているのかを格納する変数

	vector<function<void()>> UIupdatefuncVec;
	vector<function<void()>> UIinputfuncVec;
	//vector<function<void()>> UIdrawfuncVec;
};
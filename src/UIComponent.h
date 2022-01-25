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

	UIPanelCanvas* mp_UICanvasParent;  //©g‚ª‚Ç‚ÌUIScreen‚É‘¶İ‚µ‚Ä‚¢‚é‚Ì‚©‚ğŠi”[‚·‚é•Ï”

	vector<function<void()>> UIupdatefuncVec;
	vector<function<void()>> UIinputfuncVec;
	//vector<function<void()>> UIdrawfuncVec;
};
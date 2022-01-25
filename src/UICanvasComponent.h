#pragma once
#include "ofMain.h"
#include "GameActor.h"
#include "Component.h"

class UICanvasComponent : public Component
{
protected:
	vector<unique_ptr<GameActor>> m_childUIList;
	queue<unique_ptr<GameActor>> m_childUIAddQue;
public:
	UICanvasComponent(GameActor* _gactor);
	~UICanvasComponent();

	void update();
	void input();
};

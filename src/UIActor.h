#pragma once
#include "ofMain.h"
#include "Actor.h"

/*
* 抽象クラス(継承専用のクラス)
*/

class UIActor : public Actor
{
public:
	UIActor(string _name = "")
		:Actor(_name)
		, mp_UIparent(nullptr)
	{
	}

	virtual ~UIActor() = 0;

	virtual void update(float _deltaTime) = 0;
	virtual void input(float _deltaTime) = 0;
	virtual void draw() = 0;

	void RemoveAllChild();

	UIActor* mp_UIparent;  
};
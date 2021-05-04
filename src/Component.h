#pragma once
#include"ofMain.h"
//#include "GameActor.h"

class GameActor;
class Component
{
private:
	string m_componentName;
protected:
	GameActor* mp_gActor;
public:
	GameActor* gActor() {
		return mp_gActor;
	}

	virtual void update() = 0;

	Component(GameActor* _gactor, string _name = "") :mp_gActor(_gactor), m_componentName(_name) {}
	virtual ~Component() {}

	string getComponentName() { return m_componentName; }
};
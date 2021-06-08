#pragma once
#include "Parameter.h"

class GameState
{
private:
public:
	GameState() {};
	virtual ~GameState() {};
	virtual void enter(Parameter _inportprm) = 0;
	virtual GameState* update(float _deltatime) = 0;
	virtual void exit(Parameter& _reprm) = 0;
	
	GameActor* mp_actor;
	GameActor* mp_actor1;
	GameActor* mp_actor2;

	Parameter m_prmInState;
};

class GameStateTitle final : public GameState {
public:
	virtual void enter(Parameter _inportprm);
	virtual GameState* update(float _deltatime);
	virtual void exit(Parameter& _reprm);
};

class GameStateMap final : public GameState {
public:
	virtual void enter(Parameter _inportprm);
	virtual GameState* update(float _deltatime);
	virtual void exit(Parameter& _reprm);
};
#pragma once
#include "Parameter.h"

class GameState
{
private:

protected:
	GameActor* mp_fontActor;

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

// タイトルシーン
class GameStateTitle final : public GameState {
private:

public:
	virtual void enter();
	virtual GameState* update(float _deltatime);
	virtual void exit(Parameter& _reprm);
};

// マップシーン
class GameStateMap final : public GameState {
private:
	GameActor* mp_mapActor;

public:
	virtual void enter(Parameter _inportprm);
	virtual GameState* update(float _deltatime);
	virtual void exit(Parameter& _reprm);
};

// 戦闘シーン
class GameStateBattle final : public GameState {
private:

public:
	virtual void enter(Parameter _inportprm);
	virtual GameState* update(float _deltatime);
	virtual void exit(Parameter& _reprm);
};
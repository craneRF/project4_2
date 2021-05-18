#pragma once
class GameState
{
private:
public:
	GameState() {};
	virtual ~GameState() {};
	virtual void enter() = 0;
	virtual GameState* update() = 0;
	virtual void exit() = 0;
	
	GameActor* mp_actor;
	GameActor* mp_actor1;
	GameActor* mp_actor2;
};

class GameStateTitle final : public GameState {
public:
	virtual void enter();
	virtual GameState* update();
	virtual void exit();
};
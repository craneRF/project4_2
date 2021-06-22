#pragma once
class GameState
{
private:
public:
	GameState() {};
	virtual ~GameState() {};
	virtual void enter() = 0;
	virtual GameState* update(float _deltatime) = 0;
	virtual void exit() = 0;
	
	GameActor* mp_actor;
	GameActor* mp_actor1;
	GameActor* mp_actor2;
};

class GameStateTitle final : public GameState {
public:
	virtual void enter();
	virtual GameState* update(float _deltatime);
	virtual void exit();

	float m_angle;
	class MoveComponent* m_move;
};
#pragma once
#include "Component.h"

class GameState;
class GameMainCtrlComponent final : public Component
{
	friend class GameStateTitle;
	friend class GameStateMain;
	friend class GameStateGameOver;

private:
	GameState* mp_gameState;
	static GameStateTitle m_gameStateTitle;
	static GameStateMain m_gameStateMain;
	static GameStateMain m_gameStateGameOver;
public:
	 GameMainCtrlComponent(GameActor*m_gActor);
	virtual ~ GameMainCtrlComponent();

	void GameStateStart();
	void update(float _deltatime);
	bool m_isGameover;
	//int m_playerScore;
};
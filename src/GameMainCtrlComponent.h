#pragma once
#include "Component.h"

class GameState;
class GameMainCtrlComponent final : public Component
{
	friend class GameStateTitle;
	friend class GameStateMap;
	friend class GameStateBattle;

private:
	GameState* mp_gameState;
	static GameStateTitle m_gameStateTitle;
	static GameStateMap m_gameStateMap;
	static GameStateBattle m_gameStateBattle;
public:
	GameMainCtrlComponent(GameActor*m_gActor);
	virtual ~GameMainCtrlComponent();

	void GameStateStart();
	void update(float _deltatime);
	bool m_isGameover;
	//int m_playerScore;
};
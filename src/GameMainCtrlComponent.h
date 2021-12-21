#pragma once
#include "Component.h"
#include "Parameter.h"

class GameState;
class GameMainCtrlComponent final : public Component
{
	friend class GameStateTitle;
	friend class GameStateMap;
	friend class GameStateBattle;
	friend class GameStateEvent;

private:
	//Parameter m_playerprm;
	GameState* mp_gameState;
	static GameStateTitle m_gameStateTitle;
	static GameStateMap m_gameStateMap;
	static GameStateBattle m_gameStateBattle;
	static GameStateEvent m_gameStateEvent;
public:
	GameMainCtrlComponent(GameActor*m_gActor);
	virtual ~GameMainCtrlComponent();

	void GameStateStart();
	void update();
	void input() override;
	bool m_isGameover;
};
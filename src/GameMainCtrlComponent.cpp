#include  "GameMainCtrlComponent.h"
#include "GameState.h"

GameStateTitle GameMainCtrlComponent::m_gameStateTitle;
GameStateMap GameMainCtrlComponent::m_gameStateMap;
GameStateBattle GameMainCtrlComponent::m_gameStateBattle;

GameMainCtrlComponent::GameMainCtrlComponent(GameActor* _gActor) :
	Component(_gActor, "GameMainCtrlComponent")
{
}

GameMainCtrlComponent::~GameMainCtrlComponent()
{
}

void GameMainCtrlComponent::GameStateStart()
{
	mp_gameState = &m_gameStateBattle;
	//mp_gameState = &m_gameStateTitle;
	mp_gameState->enter(m_playerprm);
}

void GameMainCtrlComponent::update(float _deltatime)
{
	auto res = mp_gameState->update(_deltatime);
	if (res != nullptr) {
		mp_gameState->exit(m_playerprm);
		mp_gameState = res;
		mp_gameState->enter(m_playerprm);
	}
}

void GameMainCtrlComponent::input(float _deltatime)
{
}

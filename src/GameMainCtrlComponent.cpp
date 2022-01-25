#include  "GameMainCtrlComponent.h"
#include "GameState.h"
#include "ofApp.h"

GameStateTitle GameMainCtrlComponent::m_gameStateTitle;
GameStateClear GameMainCtrlComponent::m_gameStateClear;
GameStateOver GameMainCtrlComponent::m_gameStateOver;
GameStateMap GameMainCtrlComponent::m_gameStateMap;
GameStateBattle GameMainCtrlComponent::m_gameStateBattle;
GameStateEvent GameMainCtrlComponent::m_gameStateEvent;

GameMainCtrlComponent::GameMainCtrlComponent(GameActor* _gActor) :
	Component(_gActor, "GameMainCtrlComponent")
{
}

GameMainCtrlComponent::~GameMainCtrlComponent()
{
}

void GameMainCtrlComponent::GameStateStart()
{
	mp_gameState = &m_gameStateTitle;
	mp_gameState->enter();
}

void GameMainCtrlComponent::update()
{
	auto res = mp_gameState->update();
	if (res != nullptr) {
		mp_gameState->exit();
		mp_gameState = res;
		mp_gameState->enter();
	}
}

void GameMainCtrlComponent::input()
{
}

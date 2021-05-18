#include  "GameMainCtrlComponent.h"
#include "GameState.h"

GameStateTitle GameMainCtrlComponent::m_gameStateTitle;

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

void GameMainCtrlComponent::update(float _deltatime)
{
	auto res = mp_gameState->update(_deltatime);
	if (res != nullptr) {
		mp_gameState->exit();
		mp_gameState = res;
		mp_gameState->enter();
	}
}

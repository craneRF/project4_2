#include "BattleHUDComponent.h"
#include "GameActor.h"

BattleHUDComponent::BattleHUDComponent(GameActor * _gactor)
	: Component(_gactor, "BattleHUDComponent")
{
	gActor()->addTag("BattleHUDComponent");
}

BattleHUDComponent::~BattleHUDComponent()
{
}
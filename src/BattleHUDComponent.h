#pragma once
#include "ofMain.h"
#include "Component.h"

class GameActor;

class BattleHUDComponent  final : public Component
{
private:

public:
	BattleHUDComponent(GameActor* _gactor);
	virtual ~BattleHUDComponent();
};
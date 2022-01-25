#pragma once
#include "GameActor.h"
class PlayerActor :	public GameActor
{
public:
	PlayerActor(string _name);

	static PlayerActor* createPlayer(GameActor* _parent, ofVec3f _pos, class BattleComponent* _battleCpnt, string _name = "Player");
};
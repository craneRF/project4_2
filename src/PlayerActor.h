#pragma once
#include "GameActor.h"
class PlayerActor :	public GameActor
{
public:
	static GameActor* createPlayer(GameActor* _parent, ofVec3f _pos, string _name = "Player");
};


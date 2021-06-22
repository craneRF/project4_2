#pragma once
#include "GameActor.h"

class EnemyActor : public GameActor
{
public:
	static void createEnemy(GameActor* _parent, ofVec3f _pos, string _name = "Enemy");
};


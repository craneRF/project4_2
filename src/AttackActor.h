#pragma once
#include <memory>
#include "GameActor.h"

class AttackActor :public GameActor
{
private:

public:
	static AttackActor* createAtack(GameActor* _parent, ofVec3f _pos, string _name = "Atack");
};


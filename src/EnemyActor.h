#pragma once
#include "GameActor.h"
enum  EnemyType
{
	Nomal,
	Small,
	Big
};

class EnemyActor : public GameActor
{
public:
	static void createEnemy(GameActor* _parent, ofVec3f _pos, int _enemytype = Nomal, string _name = "Enemy");
};


#pragma once
#include "GameActor.h"
#include "EnemyObject.h"

class EnemyActor : public GameActor
{
public:
	
	static EnemyActor* createEnemy(GameActor* _parent, ofVec3f _pos, int _enemytype = Nomal, string _name = "Enemy");
	
	int getEnemyHP(int _enemytype);
	string getEnemySkill(int _enemytype);
};


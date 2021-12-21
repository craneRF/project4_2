#pragma once
#include <memory>
#include "GameActor.h"

enum EnemyType;
class EnemyBodyActor;
class BattleComponent;

class EnemyActor : public GameActor
{
private:

public:
	EnemyActor(string _name);

	static EnemyActor* createEnemy(GameActor* _parent, ofVec3f _pos, EnemyType _enemytype, BattleComponent* _battleCpnt);
};
#pragma once
#include <memory>
#include "GameActor.h"

enum EnemyType;
class EnemyBodyActor;

class EnemyActor : public GameActor
{
private:
	static string m_EnemyName;

public:
	static EnemyActor* createEnemy(GameActor* _parent, ofVec3f _pos, EnemyType _enemytype, string _name = "Enemy");
	string getEnemyName() { return m_EnemyName; }
};
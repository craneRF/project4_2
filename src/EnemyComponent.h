#pragma once
#include "Component.h"
#include "EnemyObject.h"

class GameActor;
class CollisionComponent;
class SpriteComponent;
struct EnemyParam;


class EnemyComponent  final : public Component
{
	friend class NomalEnemy;
private:
	SpriteComponent * mp_sprCpnt;
	int m_EnemyType = 0;

	static EnemyObject m_stdEnemy;
	static NomalEnemy m_nomalEnemy;
	static SmallEnemy m_smallEnemy;
public:
	EnemyComponent(GameActor* _gactor);
	virtual ~EnemyComponent();

	virtual void update(float _deltatime);
	void onCollision(CollisionComponent*);

	EnemyParam getEnemy(int _enemytype);
	void setEnemyType(int _enemytype) { m_EnemyType = _enemytype; }

};

#pragma once
#include "Component.h"
#include "EnemyObject.h"

class GameActor;
class SpriteComponent;
class CollisionComponent;
class EnemtyObj;


class EnemyComponent  final : public Component
{
	friend class NomalEnemy;
private:
	SpriteComponent * mp_sprCpnt;

	static NomalEnemy m_nomalEnemy;
	static SmallEnemy m_smallEnemy;
public:
	EnemyComponent(GameActor* _gactor);
	virtual ~EnemyComponent();

	virtual void update(float _deltatime);
	void onCollision(CollisionComponent*);

	EnemyParam getEnemy(int _enemytype);
	void discriminantEnemyType(int _enemytype);
};

#pragma once
#include "Component.h"

class GameActor;
class SpriteComponent;
class CollisionComponent;
class EnemtyObj;

class EnemyComponent  final : public Component
{
	friend class NomalEnemy;
private:
	//EnemtyObj * mp_eobj;
	SpriteComponent * mp_sprCpnt;

	static NomalEnemy m_nomalEnemy;
public:
	EnemyComponent(GameActor* _gactor);
	virtual ~EnemyComponent();

	virtual void update(float _deltatime);
	void onCollision(CollisionComponent*);
};

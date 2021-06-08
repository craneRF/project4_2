#pragma once
#include "Component.h"

class SpriteComponent;

class EnemyComponent :	public Component
{
private:
	SpriteComponent * mp_sprCpnt;
public:
	EnemyComponent(GameActor* _gactor);
	virtual ~EnemyComponent();

	virtual void update(float _deltatime);
	void onCollision(CollisionComponent*);
};

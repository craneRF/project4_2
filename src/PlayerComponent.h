#pragma once
#include "Component.h"

class GameActor;
class EnemtyObj;
class CollisionComponent;
class SpriteComponent;

class PlayerComponent :public Component
{
private:
	EnemtyObj * mp_eobj;
	SpriteComponent * mp_sprCpnt;

public:
	PlayerComponent(GameActor *_gactor);
	virtual ~PlayerComponent();

	virtual void update(float _deltatime);
	void onCollision(CollisionComponent*);


};
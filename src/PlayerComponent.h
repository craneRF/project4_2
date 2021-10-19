#pragma once
#include "Component.h"

class GameActor;
class CollisionComponent;
class SpriteComponent;

class PlayerComponent :public Component
{
private:

	SpriteComponent * mp_sprCpnt;

public:
	PlayerComponent(GameActor *_gactor);
	virtual ~PlayerComponent();

	virtual void update();
	virtual void input();
	void onCollision(CollisionComponent*);


};
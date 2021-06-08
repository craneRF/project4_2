#pragma once
#include "Component.h"

class GameActor;
//class PlayerObj;
class CollisionComponent;
class SpriteComponent;

class PlayerComponent :public Component
{
private:
	//PlayerObj * mp_pobj;
	SpriteComponent * mp_sprCpnt;

public:
	PlayerComponent(GameActor *_gactor);
	virtual ~PlayerComponent();

	virtual void update(float _deltatime);
	void onCollision(CollisionComponent*);


};
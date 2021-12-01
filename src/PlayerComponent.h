#pragma once
#include "Component.h"

class GameActor;
class CollisionComponent;
class SpriteComponent;

class PlayerComponent :public Component
{
private:
	ofVec3f m_imageSize;

public:
	PlayerComponent(GameActor *_gactor);
	virtual ~PlayerComponent();

	virtual void update();
	virtual void input();
	void onCollision(CollisionComponent*);

	ofVec3f GetImageSize() const { return m_imageSize; }
};
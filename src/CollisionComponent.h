#pragma once
#include "Component.h"
#include "CollisionManager.h"

class GameActor;
class CollisionObj;

class CollisionComponent: public Component
{
private:
	CollisionObj* mp_cobj;
	float m_width, m_height;
	ofVec3f m_offset;

public:
	CollisionComponent(GameActor* _gactor)
		: Component(_gactor, "CollisionComponent")
		, m_onCollisionFunc([](CollisionComponent* _other) {})
	{
	}

	function<void(CollisionComponent* _other)> m_onCollisionFunc;

	virtual ~CollisionComponent() = 0
	{
	}
	//void initialize(ofVec3f _offset, float _width,float _height, CollisionType _ctype);

};
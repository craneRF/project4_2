#pragma once
#include "Component.h"
#include "CollisionManager.h"

class GameActor;
class CollisionObj;

class CollisionComponent: public Component
{
public:
	enum class Shape {  //�Փ˔���̌`
		ERectangle  //�l�p(BoxComponent�Ɏg��)
		, ECircle  //�~(CircleComponent�Ɏg��)
	};

	CollisionComponent(GameActor* _gactor, Shape _shape)
		: Component(_gactor, "CollisionComponent")
		, m_shape(_shape)
		, m_onCollisionFunc([](CollisionComponent* _other) {})
	{
	}

	CollisionObj* mp_cobj;
	function<void(CollisionComponent* _other)> m_onCollisionFunc;

	const Shape m_shape;

	virtual ~CollisionComponent() = 0
	{
	}
	//void initialize(ofVec3f _offset, float _width,float _height, CollisionType _ctype);

	CollisionType GetColType();
};
#pragma once
#include "CollisionComponent.h"

class CollisionObj;

class BoxComponent : public CollisionComponent
{
private:
	CollisionObj* mp_cobj;

	float m_width, m_height;
	ofVec3f m_offset;

public:
	BoxComponent(GameActor* _gactor);
	//function<void(CollisionComponent* _other)> m_onCollisionFunc;

	virtual ~BoxComponent();
	void update() override;
	void input() override;
	void initialize(ofVec3f _offset, float _width, float _height, CollisionType _ctype);

};
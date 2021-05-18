#pragma once
#include "Component.h"
#include "GameActor.h"

class MoveComponent :public Component
{
private:

public:
	MoveComponent(GameActor* _gator);
	virtual ~MoveComponent();
	virtual void update(float _deltatime);

	void setMoveVec(ofVec3f _vec);
	void setAngle(float _degree, float _speed);

	ofVec3f m_movevec;
};
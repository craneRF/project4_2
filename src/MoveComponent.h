#pragma once
#include "Component.h"
#include "GameActor.h"

class MoveComponent :public Component
{
private:
	ofVec3f m_movePos;
	float m_moveDeg;

public:
	MoveComponent(GameActor* _gator);
	virtual ~MoveComponent();
	virtual void update(float _deltatime);
	void input(float _deltatime) override;

	void FrontMove(float _speed = 1.0f);


public:
	inline void AddMovePos(ofVec3f _add)
	{
		m_movePos += _add;
	}
	inline void AddMoveAngle(float _add)
	{
		m_moveDeg += _add;
	}
};
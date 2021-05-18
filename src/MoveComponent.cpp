#include "MoveComponent.h"

MoveComponent::MoveComponent(GameActor* _gactor) :
	Component(_gactor, "MoveComponent")
	, m_movevec({0,0,0})
{
}

MoveComponent::~MoveComponent()
{

}

void MoveComponent::update(float _deltatime)
{
	mp_gActor->Pos() += m_movevec * _deltatime;
}

void MoveComponent::setMoveVec(ofVec3f _vec)
{
	m_movevec = _vec;
}

void MoveComponent::setAngle(float _degree, float _speed)
{
	mp_gActor->RotAngle() = _degree;
	setMoveVec(
		{ cosf(ofDegToRad(_degree)) * _speed,-sinf(ofDegToRad(_degree)) * _speed,0 }
	);
};
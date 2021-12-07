#include "MoveComponent.h"

MoveComponent::MoveComponent(GameActor* _gactor) :
	Component(_gactor, "MoveComponent")
	, m_movePos({0,0,0})
	, m_moveDeg(0.0f)
	, m_isOnceMove(true)
{
}

MoveComponent::~MoveComponent()
{

}

void MoveComponent::update()
{
	mp_gActor->Pos() += m_movePos * mp_gActor->DeltaTime();
	mp_gActor->RotAngle() -= m_moveDeg * mp_gActor->DeltaTime();

	if (m_isOnceMove)
	{
		m_movePos = { 0.0f, 0.0f, 0.0f };
		m_moveDeg = 0.0f;
	}
}

void MoveComponent::input()
{
}

void MoveComponent::FrontMove(float _speed)
{
	m_movePos += { cosf(ofDegToRad(mp_gActor->RotAngle())) * _speed,-sinf(ofDegToRad(mp_gActor->RotAngle())) * _speed,0 };
}
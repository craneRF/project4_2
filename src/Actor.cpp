#include "Actor.h"

Actor::Actor(string _name)
	: m_pos(ofVec3f(0, 0, 0))
	, m_rotAngle(0)
	, m_worldRotAngle(0)
	, m_scale({ 1,1,1 })
	, m_name(_name)
	, drawfunc([]() {})
	, m_ActorState(ActorState::EActive)
	, m_ActorDrawState(ActorDrawState::EVisible)
{

}

Actor::~Actor()
{
}

void Actor::caluculateWorldTransform()
{
	if (m_rotAngle >= 360.0f) {
		m_rotAngle = 0.0f;
	}

	this->m_worldScale = this->m_scale;
	this->m_worldRotAngle = this->m_rotAngle;
	this->m_worldPos = this->m_pos.getRotated(-(this->m_rotAngle), ofVec3f(0, 0, 1)) * this->m_scale;
}

void Actor::initialize(ofVec3f _pos, string _name)
{
	this->m_pos = _pos;
	this->m_name = _name;
	this->caluculateWorldTransform();
}

void Actor::draw()
{
	if (GetActorDrawState() == ActorDrawState::EVisible) {
		ofPushMatrix();
		ofTranslate(this->m_worldPos);
		ofRotateDeg(-(this->m_worldRotAngle));
		ofScale(this->m_worldScale);

		assert(this->drawfunc != nullptr);
		this->drawfunc();
		ofPopMatrix();
	}
}

void Actor::setParam(ofVec3f _pos, ofVec3f _scale, float _angle)
{
	this->Pos() = _pos;
	this->Scale() = _scale;
	this->RotAngle() = _angle;
}

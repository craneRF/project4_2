#include "Actor.h"

Actor::Actor(string _name)
	: m_pos(ofVec3f(0, 0, 0))
	, m_rotAngle(0)
	, m_worldRotAngle(0)
	, m_scale({ 1,1,1 })
	, m_name(_name)
	, drawfunc([]() {})
{

}

Actor::~Actor()
{
}

void Actor::caluculateWorldTransform()
{
	m_worldScale = m_scale;
	m_worldRotAngle = m_rotAngle;
	m_worldPos = m_pos.getRotated(-m_rotAngle, ofVec3f(0, 0, 1)) * m_scale;
}

void Actor::initialize(ofVec3f _pos, string _name)
{
	m_pos = _pos;
	m_name = _name;
	this->caluculateWorldTransform();
}

void Actor::draw()
{
	ofPushMatrix();
	ofTranslate(m_worldPos);
	ofRotateDeg(-m_worldRotAngle);
	ofScale(m_worldScale);

	assert(drawfunc != nullptr);
	drawfunc();
	ofPopMatrix();
}

void Actor::setParam(ofVec3f _pos, ofVec3f _scale, float _angle)
{
	Pos() = _pos;
	Scale() = _scale;
	RotAngle() = _angle;
}

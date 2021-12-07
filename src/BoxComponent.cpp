#include "ofApp.h"
#include "BoxComponent.h"

BoxComponent::BoxComponent(GameActor* _gactor) :
	CollisionComponent(_gactor, CollisionComponent::Shape::ERectangle)
{
	mp_cobj = ofApp::getInstance()->mp_collisionManager->getObj(this);
}

void BoxComponent::initialize(ofVec3f _offset, float _width, float _height, CollisionType _ctype) {
	m_offset = _offset;
	m_width = _width;
	m_height = _height;
	mp_cobj->m_ctype = _ctype;
	auto centerOfs = ofVec3f(m_width * 0.5f, m_height * 0.5f);
	mp_cobj->setCollisionBox(ofRectangle(gActor()->WorldPos() + m_offset - centerOfs, m_width, m_height));
}

BoxComponent::~BoxComponent() {
	ofApp::getInstance()->mp_collisionManager->releaseObj(mp_cobj);
}

void BoxComponent::update() {
	ofVec3f scaledSize = { m_width * mp_gActor->WorldScale().x, m_height * mp_gActor->WorldScale().y };
	auto centerOfs = ofVec3f(scaledSize.x * 0.5f, scaledSize.y * 0.5f);
	mp_cobj->setCollisionBox(ofRectangle(gActor()->WorldPos() + m_offset - centerOfs, scaledSize.x, scaledSize.y));
}

void BoxComponent::input()
{
}
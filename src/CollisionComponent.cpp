#include "ofApp.h"
#include "CollisionComponent.h"
#include "GameActor.h"

CollisionComponent::CollisionComponent(GameActor* _gactor) :
	Component(_gactor, "CollisionComponent"),
	mp_cobj(ofApp::getInstance()->mp_collisionManager->getObj(this)),
	m_onCollisionFunc([](CollisionComponent* _other) {})
{
}

void CollisionComponent::initialize(ofVec3f _offset, float _width, float _height, CollisionType _ctype) {
	m_offset = _offset;
	m_width = _width;
	m_height = _height;
	mp_cobj->m_ctype = _ctype;
	auto centerOfs = ofVec3f(m_width * 0.5f, m_height * 0.5f);
	mp_cobj->setCollisionParam(ofRectangle(mp_gActor->WorldPos() + m_offset - centerOfs, m_width, m_height));
}

CollisionComponent::~CollisionComponent() {
	ofApp::getInstance()->mp_collisionManager->releaseObj(mp_cobj);
}

void CollisionComponent::update(float _deltatime) {
	ofVec3f scaledSize = { m_width * mp_gActor->WorldScale().x, m_height * mp_gActor->WorldScale().y };
	auto centerOfs = ofVec3f(scaledSize.x * 0.5f, scaledSize.y * 0.5f);
	mp_cobj->setCollisionParam(ofRectangle(mp_gActor->WorldPos() + m_offset - centerOfs, scaledSize.x, scaledSize.y));
}

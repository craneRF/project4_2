#include "SpriteComponent.h"
#include "GameActor.h"

SpriteComponent::SpriteComponent(GameActor* _gactor) :
	Component(_gactor, "SpriteComponent"), mp_image(nullptr), mp_offset({ 0,0,0 })
{
	m_color = ofColor::white;
	mp_gActor->drawfunc = std::bind(&SpriteComponent::draw, this);
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::update(float _deltatime)
{
}

void SpriteComponent::draw()
{
	if (!m_enabled) return;
	ofSetColor(m_color);
	mp_image->draw(mp_offset);
}

void SpriteComponent::setImage(ofImage* _img)
{
	mp_image = _img;
}

bool& SpriteComponent::enabled()
{
	return m_enabled;
}

ofVec3f& SpriteComponent::offset()
{
	return mp_offset;
}

void SpriteComponent::AlignPivotCenter()
{
	offset() = { -mp_image->getWidth() / 2 ,-mp_image->getHeight() / 2 };
}


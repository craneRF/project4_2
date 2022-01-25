#include "HitEffectComponent.h"
#include "ofApp.h"
#include "stdComponent.h"

HitEffectComponent::HitEffectComponent(GameActor * _gator) :
	Component(_gator, "HitEffectComponent"),
	m_liveFrame(60),
	m_frameCount(0)
{
}

HitEffectComponent::~HitEffectComponent()
{
}

void HitEffectComponent::update()
{
	if (++m_frameCount >= m_liveFrame) {
		mp_gActor->StateErace();
	}
}

void HitEffectComponent::input()
{
}

void HitEffectComponent::Initialize(const string & _fileName, const int _effectSize)
{
	// スプライトコンポーネント
	auto spriteCpnt = mp_gActor->addComponent<SpriteComponent>();
	spriteCpnt->initialize(_fileName);
	float scale = _effectSize / max(spriteCpnt->ImageSize().x, spriteCpnt->ImageSize().y);
	mp_gActor->Scale() = { scale ,scale ,1 };
	spriteCpnt->AlignPivotCenter();

}

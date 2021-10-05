#include "ofApp.h"
#include "SpriteComponent.h"
#include "AnimSeq.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(GameActor * _gactor) : Component(_gactor,
	"AnimationComponent"),
	m_remainTime(0), m_nowIdx(0), mp_sprCpnt(nullptr),
	mp_animSeq(nullptr) {
}

AnimationComponent::~AnimationComponent() {
}

void AnimationComponent::initialize(AnimSeq * _animSeq) {
	mp_sprCpnt = mp_gActor->getComponent<SpriteComponent>();
	assert(mp_sprCpnt != nullptr);
	mp_animSeq = _animSeq;
	m_nowIdx = 0;
	setNextSprite(m_nowIdx);
}

void AnimationComponent::update() {
	assert(mp_animSeq != nullptr);
	--m_remainTime;
	if (m_remainTime <= 0) {
		m_nowIdx = mp_animSeq->getFrame(m_nowIdx).m_next;

		// アニメーション終わり
		if (m_nowIdx == -1)
		{
			mp_gActor->waitforErase_ = true;
			return;
		}
		setNextSprite(m_nowIdx);
	}
}

void AnimationComponent::setNextSprite(int _idx) {
	mp_sprCpnt->setImage(mp_animSeq->getFrame(_idx).mp_image);
	mp_sprCpnt->offset() = mp_animSeq->getFrame(_idx).m_offset;
	mp_sprCpnt->enabled() = mp_animSeq->getFrame(_idx).m_visible;
	m_remainTime = mp_animSeq->getFrame(_idx).m_time;
	m_nowIdx = _idx;
	ofVec3f intejer;
}

void AnimationComponent::setAnim(AnimSeq* _animSeq)
{
	mp_animSeq = _animSeq;
	m_nowIdx = 0;
	setNextSprite(m_nowIdx);
}


#pragma once
#include "Component.h"

class SpriteComponent;
class AnimSeq;

class AnimationComponent final : public Component
{
private:
	SpriteComponent * mp_sprCpnt;
	AnimSeq * mp_animSeq;
	int m_nowIdx;
	int m_remainTime;
public:
	AnimationComponent(GameActor*_gactor);
	virtual ~AnimationComponent();

	void initialize(AnimSeq* _animSeq);
	virtual void update();
	void input() override;
	void setNextSprite(int _idx);
	void setAnim(AnimSeq * _animSeq);
};
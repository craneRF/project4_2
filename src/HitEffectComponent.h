#pragma once
#include "Component.h"

class HitEffectComponent :public Component
{
private:
	const int m_liveFrame;
	int m_frameCount;

public:
	HitEffectComponent(GameActor* _gator);
	virtual ~HitEffectComponent();
	virtual void update();
	virtual void input();

	// ‰Šú‰»
	void Initialize(const string& _fileName, const int _effectSize);
};
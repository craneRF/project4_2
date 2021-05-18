#pragma once
#include "ofMain.h"
#include "Component.h"

class SpriteComponent : public Component
{
private:
	ofImage* mp_image;
	ofVec3f mp_offset;
	bool m_enabled;
public:
	SpriteComponent(GameActor* _gactor);
	virtual ~SpriteComponent();
	virtual void update();

	void draw();
	void setImage(ofImage* _img);
	bool& enabled();
	ofVec3f& offset();

	void AlignPivotCenter();
};
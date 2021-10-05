#pragma once
#include "ofMain.h"
#include "Component.h"

class SpriteComponent : public Component
{
private:
	ofImage* mp_image;
	ofVec3f mp_offset;
	bool m_enabled;
	ofColor m_color;
public:
	SpriteComponent(GameActor* _gactor);
	virtual ~SpriteComponent();
	virtual void update(float _deltatime);

	void draw();
	void setImage(ofImage* _img);
	bool& enabled();
	ofVec3f& offset();
	void SetColor(ofColor _color) { m_color = _color; }
	void AlignPivotCenter();
	const ofVec3f ImageSize() { return ofVec3f(mp_image->getWidth(), mp_image->getHeight()); }
};
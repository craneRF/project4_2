#include "UICommon.h"

UICommon::UICommon(string _name)
{
}

UICommon::~UICommon()
{
}

void UICommon::caluculateWorldTransform()
{
	if (this->RotAngle() >= 360.0f) {
		this->RotAngle() = 0.0f;
	}

	if (mp_UIparent != nullptr) {
		this->WorldScale() = mp_UIparent->WorldScale() * this->Scale();
		this->WorldRotAngle() = mp_UIparent->WorldRotAngle() + this->RotAngle();
		this->WorldPos() = mp_UIparent->WorldPos() +
			this->Pos().getRotated(-(mp_UIparent->WorldRotAngle()), ofVec3f(0, 0, 1)) *
			mp_UIparent->WorldScale();
	}
	else {
		this->WorldScale() = this->Scale();
		this->WorldRotAngle() = this->RotAngle();
		this->WorldPos() = this->Pos().getRotated(-(this->RotAngle()), ofVec3f(0, 0, 1)) * this->Scale();
	}
}

void UICommon::update(float _deltaTime)
{
	
}

void UICommon::input(float _deltaTime)
{
}

void UICommon::draw()
{
	if (GetActorDrawState() == ActorDrawState::EVisible) {
		ofPushMatrix();
		ofTranslate(this->m_worldPos);
		ofRotateDeg(-(this->m_worldRotAngle));
		ofScale(this->m_worldScale);

		assert(this->drawfunc != nullptr);
		this->drawfunc();
		ofPopMatrix();
	}
}
#include "ofApp.h"
#include "UICommon.h"
#include "UIPanel.h"

UICommon::UICommon(string _name)
	:Actor(_name)
	,mp_UIPanelParent(nullptr)
	,UIupdatefunc([]() {})
	,UIinputfunc([]() {})
	,UIdrawfunc([]() {})
{
	mp_fontRenderer = make_unique<FontRenderer>();
	mp_TexRenderer = make_unique<TextureRenderer>();
}

UICommon::~UICommon()
{
}

void UICommon::caluculateWorldTransform()
{
	if (this->RotAngle() >= 360.0f) {
		this->RotAngle() = 0.0f;
	}

	if (mp_UIPanelParent != nullptr) {
		this->WorldScale() = mp_UIPanelParent->WorldScale() * this->Scale();
		this->WorldRotAngle() = mp_UIPanelParent->WorldRotAngle() + this->RotAngle();
		this->WorldPos() = mp_UIPanelParent->WorldPos() +
			this->Pos().getRotated(-(mp_UIPanelParent->WorldRotAngle()), ofVec3f(0, 0, 1)) *
			mp_UIPanelParent->WorldScale();
	}
	else {
		this->WorldScale() = this->Scale();
		this->WorldRotAngle() = this->RotAngle();
		this->WorldPos() = this->Pos().getRotated(-(this->RotAngle()), ofVec3f(0, 0, 1)) * this->Scale();
	}
}

void UICommon::update()
{
	caluculateWorldTransform();
	m_actorDelta = ofApp::getInstance()->m_deltaTime;

	if (GetActorState() != ActorState::EPause) {
		this->UIupdatefunc();
	}
}

void UICommon::input()
{
	if (GetActorState() == ActorState::EActive) {
		this->UIinputfunc();
	}
}

void UICommon::draw()
{
	ofPushMatrix();
	/*ofTranslate(this->m_worldPos);
	ofRotateDeg(-(this->m_worldRotAngle));
	ofScale(this->m_worldScale);*/

	assert(this->UIdrawfunc != nullptr);
	this->UIdrawfunc();
	ofPopMatrix();
}
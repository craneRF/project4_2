#include "ofApp.h"
#include "UICommon.h"
#include "UIPanel.h"

UICommon::UICommon(string _name)
	:Actor(_name)
	,mp_UIPanelParent(nullptr)
	//,UIupdatefunc([]() {})
	//,UIinputfunc([]() {})
	//,UIdrawfunc([]() {})
{
	mp_fontRenderer = make_unique<FontRenderer>();
	mp_TexRenderer = make_unique<TextureRenderer>();

	UIupdatefuncVec.emplace_back(bind(&UICommon::caluculateWorldTransform, this));
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
		this->WorldScale() = this->Scale()* ((float)ofGetHeight() / (float)Define::FULLWIN_H);
		this->WorldRotAngle() = this->RotAngle();
		this->WorldPos() = this->Pos().getRotated(-(this->RotAngle()), ofVec3f(0, 0, 1)) * this->Scale()* ((float)ofGetHeight() / (float)Define::FULLWIN_H);
	}
}

void UICommon::update()
{
	caluculateWorldTransform();
	m_actorDelta = ofApp::getInstance()->m_deltaTime;

	if (GetActorState() != ActorState::EPause) {
		//this->UIupdatefunc();
		for (auto uf : this->UIupdatefuncVec) {
			assert(uf != nullptr);
			uf();
		}
	}
}

void UICommon::input()
{
	//if (GetActorState() == ActorState::EActive) {
	//	for (auto& inf : this->UIinputfuncVec) {
	//		assert(inf != nullptr);
	//		inf();
	//	}
	//	//this->UIinputfunc();
	//}
}

void UICommon::draw()
{
	for (auto& df : this->UIdrawfuncVec) {
		assert(df != nullptr);
		ofPushMatrix();
	/*ofTranslate(this->m_worldPos);
	ofRotateDeg(-(this->m_worldRotAngle));
	ofScale(this->m_worldScale);*/
		df();
		//this->UIdrawfunc();
		ofPopMatrix();
	}
}
#include "ofApp.h"
#include "UIPanel.h"

UIPanel::UIPanel(string _name)
	:Actor(_name)
	,mp_UIPanelParent(nullptr)
	,mp_UICanvasParent(nullptr)
{
	m_UICommonChildList.clear();
	m_UIPanelChildList.clear();
}

UIPanel::~UIPanel()
{
}

void UIPanel::caluculateWorldTransform()
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

void UIPanel::update()
{
	caluculateWorldTransform();
	m_actorDelta = ofApp::getInstance()->m_deltaTime;

	//削除予定UICommonの削除
	if (!m_UICommonChildList.empty()) {
		m_UICommonChildList.erase(
			remove_if(m_UICommonChildList.begin(), m_UICommonChildList.end(),
				[](const auto& uic) {return uic->GetActorState() == ActorState::EErace; }),
			m_UICommonChildList.end()
		);
	}

	//追加待ちUICommonの追加処理
	while (!m_UICommonChildAddQue.empty()) {
		m_UICommonChildList.push_back(move(m_UICommonChildAddQue.front()));
		m_UICommonChildAddQue.pop();
	}
	//子UICommonの全件処理
	if (!m_UICommonChildList.empty()) {
		for (auto& uic : m_UICommonChildList)
		{
			if (uic->GetActorState() != ActorState::EPause) {
				uic->update();  //描画に影響する処理などはEActive状態とEDrawing状態の時に行う
			}
		}
	}

	//削除予定UIPanelの削除
	if (!m_UIPanelChildList.empty()) {
		m_UIPanelChildList.erase(
			remove_if(m_UIPanelChildList.begin(), m_UIPanelChildList.end(),
				[](const auto& uic) {return uic->GetActorState() == ActorState::EErace; }),
			m_UIPanelChildList.end()
		);
	}

	//追加待ちUIPanelの追加処理
	while (!m_UIPanelChildAddQue.empty()) {
		m_UIPanelChildList.push_back(move(m_UIPanelChildAddQue.front()));
		m_UIPanelChildAddQue.pop();
	}
	//子UIPanelの全件処理
	if (!m_UIPanelChildList.empty()) {
		for (auto& uic : m_UIPanelChildList)
		{
			if (uic->GetActorState() != ActorState::EPause) {
				uic->update();  //描画に影響する処理などはEActive状態とEDrawing状態の時に行う
			}
		}
	}
}

void UIPanel::input()
{
	if (!m_UICommonChildList.empty()) {
		for (auto& uic : m_UICommonChildList)
		{
			if (uic->GetActorState() == ActorState::EActive) {
				uic->UIinputfunc();  //操作処理はEActive状態のUIScreenしか行わない
			}
		}
	}

	if (!m_UIPanelChildList.empty()) {
		for (auto& uic : m_UIPanelChildList)
		{
			if (uic->GetActorState() == ActorState::EActive) {
				uic->input();  //操作処理はEActive状態のUIScreenしか行わない
			}
		}
	}
}

void UIPanel::draw()
{
	if (!m_UICommonChildList.empty()) {
		for (auto& uic : m_UICommonChildList) {
			if (uic->GetActorDrawState() == ActorDrawState::EVisible) {
				ofPushMatrix();
				ofTranslate(uic->WorldPos());
				ofRotateDeg(-(uic->WorldRotAngle()));
				ofScale(uic->WorldScale());

				assert(uic->UIdrawfunc != nullptr);
				uic->UIdrawfunc();
				ofPopMatrix();
			}
		}
	}

	if (!m_UIPanelChildList.empty()) {
		for (auto& uic : m_UIPanelChildList) {
			if (uic->GetActorDrawState() == ActorDrawState::EVisible) {
				uic->draw();
			}
		}
	}
}

void UIPanel::RemoveAllChild()
{
	queue<unique_ptr<UICommon>>().swap(m_UICommonChildAddQue);	//queueの全消し
	for (auto& uic : m_UICommonChildList) {
		uic->StateErace();
	}

	queue<unique_ptr<UIPanel>>().swap(m_UIPanelChildAddQue);	//queueの全消し
	for (auto& uic : m_UIPanelChildList) {
		uic->StateErace();
	}
}
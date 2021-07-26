#include "UIPanel.h"

UIPanel::UIPanel(string _name)
	:Actor(_name)
	,mp_UIPanelParent(nullptr)
	,mp_UIScreenParent(nullptr)
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

void UIPanel::update(float _deltaTime)
{
	caluculateWorldTransform();

	//�폜�\��UICommon�̍폜
	if (!m_UICommonChildList.empty()) {
		m_UICommonChildList.erase(
			remove_if(m_UICommonChildList.begin(), m_UICommonChildList.end(),
				[](const auto& uic) {return uic->GetActorState() == ActorState::EErace; }),
			m_UICommonChildList.end()
		);
	}

	//�ǉ��҂�UICommon�̒ǉ�����
	while (!m_UICommonChildAddQue.empty()) {
		m_UICommonChildList.push_back(move(m_UICommonChildAddQue.front()));
		m_UICommonChildAddQue.pop();
	}
	//�qUICommon�̑S������
	if (!m_UICommonChildList.empty()) {
		for (auto& uic : m_UICommonChildList)
		{
			if (uic->GetActorState() != ActorState::EPause) {
				uic->update(_deltaTime);  //�`��ɉe�����鏈���Ȃǂ�EActive��Ԃ�EDrawing��Ԃ̎��ɍs��
			}
		}
	}

	//�폜�\��UIPanel�̍폜
	if (!m_UIPanelChildList.empty()) {
		m_UIPanelChildList.erase(
			remove_if(m_UIPanelChildList.begin(), m_UIPanelChildList.end(),
				[](const auto& uic) {return uic->GetActorState() == ActorState::EErace; }),
			m_UIPanelChildList.end()
		);
	}

	//�ǉ��҂�UIPanel�̒ǉ�����
	while (!m_UIPanelChildAddQue.empty()) {
		m_UIPanelChildList.push_back(move(m_UIPanelChildAddQue.front()));
		m_UIPanelChildAddQue.pop();
	}
	//�qUIPanel�̑S������
	if (!m_UIPanelChildList.empty()) {
		for (auto& uic : m_UIPanelChildList)
		{
			if (uic->GetActorState() != ActorState::EPause) {
				uic->update(_deltaTime);  //�`��ɉe�����鏈���Ȃǂ�EActive��Ԃ�EDrawing��Ԃ̎��ɍs��
			}
		}
	}
}

void UIPanel::input(float _deltaTime)
{
	if (!m_UICommonChildList.empty()) {
		for (auto& uic : m_UICommonChildList)
		{
			if (uic->GetActorState() == ActorState::EActive) {
				uic->input(_deltaTime);  //���쏈����EActive��Ԃ�UIScreen�����s��Ȃ�
			}
		}
	}

	if (!m_UIPanelChildList.empty()) {
		for (auto& uic : m_UIPanelChildList)
		{
			if (uic->GetActorState() == ActorState::EActive) {
				uic->input(_deltaTime);  //���쏈����EActive��Ԃ�UIScreen�����s��Ȃ�
			}
		}
	}
}

void UIPanel::draw()
{
	if (!m_UICommonChildList.empty()) {
		for (auto& uic : m_UICommonChildList) {
			if (uic->GetActorDrawState() == ActorDrawState::EVisible) {
				uic->draw();
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
	queue<unique_ptr<UICommon>>().swap(m_UICommonChildAddQue);	//queue�̑S����
	for (auto& uic : m_UICommonChildList) {
		uic->StateErace();
	}

	queue<unique_ptr<UIPanel>>().swap(m_UIPanelChildAddQue);	//queue�̑S����
	for (auto& uic : m_UIPanelChildList) {
		uic->StateErace();
	}
}
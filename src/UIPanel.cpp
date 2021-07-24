#include "UIPanel.h"

UIPanel::UIPanel(string _name)
	:UIActor(_name)
{
	m_UIchildList.clear();
}

UIPanel::~UIPanel()
{
}

void UIPanel::caluculateWorldTransform()
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

void UIPanel::update(float _deltaTime)
{
	caluculateWorldTransform();

	//�폜�\��UI�A�N�^�[�̍폜
	m_UIchildList.erase(
		remove_if(m_UIchildList.begin(), m_UIchildList.end(),
			[](const auto& uic) {return uic->GetActorState() == ActorState::EErace; }),
		m_UIchildList.end()
	);

	//�ǉ��҂�UI�A�N�^�[�̒ǉ�����
	while (!m_UIchildAddQue.empty()) {
		m_UIchildList.push_back(move(m_UIchildAddQue.front()));
		m_UIchildAddQue.pop();
	}
	//�qUI�A�N�^�[�̑S������
	for (auto& uic : m_UIchildList)
	{
		if (uic->GetActorState() != ActorState::EPause) {
			uic->update(_deltaTime);  //�`��ɉe�����鏈���Ȃǂ�EActive��Ԃ�EDrawing��Ԃ̎��ɍs��
		}
	}
}

void UIPanel::input(float _deltaTime)
{
	for (auto& uic : m_UIchildList)
	{
		if (uic->GetActorState() == ActorState::EActive) {
			uic->input(_deltaTime);  //���쏈����EActive��Ԃ�UIScreen�����s��Ȃ�
		}
	}
}

void UIPanel::draw()
{
	for (auto& uic : m_UIchildList) {
		if (uic->GetActorDrawState() == ActorDrawState::EVisible) {
			uic->draw();
		}
	}

}

void UIPanel::RemoveAllChild()
{
	queue<unique_ptr<UIActor>>().swap(m_UIchildAddQue);	//queue�̑S����
	for (auto& uic : m_UIchildList) {
		uic->StateErace();
	}
}
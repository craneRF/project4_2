#include "UIPanel.h"

UIPanel::UIPanel(string _name)
	:UIActor(_name)
{
	m_UIchildList.clear();
}

UIPanel::~UIPanel()
{
}

void UIPanel::update(float _deltaTime)
{
	Actor::caluculateWorldTransform();

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
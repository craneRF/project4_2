#include "ofApp.h"
#include "UIScreen.h"
#include "UISprite.h"

UIScreen::UIScreen(string _name)
	:m_screenName(_name)
	,m_UIScreenState(UIScreenState::EActive)
	,m_UIScreenDrawState(UIScreenDrawState::EVisible)
{
}

UIScreen::~UIScreen()
{
}

void UIScreen::initialize()
{
}

void UIScreen::update(float _deltaTime)
{
	//�폜�\��UI�A�N�^�[�̍폜
	m_UIActorList.erase(
		remove_if(m_UIActorList.begin(), m_UIActorList.end(),
			[](const auto& uia) {return uia->GetActorState() == Actor::ActorState::EErace; }),
		m_UIActorList.end()
	);

	//�ǉ��҂�UI�A�N�^�[�̒ǉ�����
	while (!m_UIActorAddQue.empty()) {
		m_UIActorList.push_back(move(m_UIActorAddQue.front()));
		m_UIActorAddQue.pop();
	}
	//�qUI�A�N�^�[�̑S������
	for (auto& uia : m_UIActorList)
	{
		if (uia->GetActorState() != Actor::ActorState::EPause) {
			uia->update(_deltaTime);  //�`��ɉe�����鏈���Ȃǂ�EActive��Ԃ�EDrawing��Ԃ̎��ɍs��
		}
	}
}

void UIScreen::input(float _deltaTime)
{
	for (auto& uia : m_UIActorList)
	{
		if (uia->GetActorState() == Actor::ActorState::EActive) {
			uia->input(_deltaTime);  //���쏈����EActive��Ԃ�UIScreen�����s��Ȃ�
		}
	}
}

void UIScreen::draw()
{
	for (auto& uia : m_UIActorList) {
		if (uia->GetActorDrawState() == Actor::ActorDrawState::EVisible) {
			uia->draw();
		}
	}
}

void UIScreen::RemoveAllUIActor()
{
	queue<unique_ptr<UIActor>>().swap(m_UIActorAddQue);	//queue�̑S����
	for (auto& uia : m_UIActorList) {
		uia->StateErace();
	}
}

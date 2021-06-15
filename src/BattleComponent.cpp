#include "BattleComponent.h"
#include "ofApp.h"

BattleComponent::BattleComponent(GameActor* _gactor) :
	Component(_gactor, "BattleComponent")
{
}

BattleComponent::~BattleComponent()
{

}

void BattleComponent::update(float _deltatime)
{
	bool down = ofApp::getInstance()->mp_inputManager->getButtonDown("Down");
	bool up = ofApp::getInstance()->mp_inputManager->getButtonDown("Up");
	bool start = ofApp::getInstance()->mp_inputManager->getButtonDown("Start");
	m_result = Result::NONE;

	if (down)
	{
		m_selectIndex++;
	}
	else if (up)
	{
		m_selectIndex--;
	}
	// ����
	else if (start)
	{
		if (m_start)
		{
			m_selectIndex = 0;
		}
		else
		{
			m_start = true;
		}
	}
	
	// �f�����Ȃǂ�����΂��̏��ōs���������߂�
	// ������s��������
	// �s�����I�������^�[����؂�ւ���
	// ����������s��������
	// ���s��������I���
	switch (m_turn)
	{
	case Turn::NONE:

		break;
	case Turn::ME:

		break;
	case Turn::ENEMY:

		break;
	default:
		break;
	}

	CheckResult();

	// �L�����̕`��
	mp_gActor->drawfunc = [&]
	{
	};
}

void BattleComponent::CheckResult()
{
	m_result = Result::NONE;
}

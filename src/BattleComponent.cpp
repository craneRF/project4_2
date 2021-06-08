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
	// 決定
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
	
	// 素早さなどがあればその情報で行動順を決める
	// 一方を行動させる
	// 行動が終わったらターンを切り替える
	// もう一方を行動させる
	// 勝敗がついたら終わり
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

	// キャラの描画
	mp_gActor->drawfunc = [&]
	{
	};
}

void BattleComponent::CheckResult()
{
	m_result = Result::NONE;
}

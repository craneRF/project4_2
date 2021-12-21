#include "BattleState.h"
#include "stdComponent.h"
#include "EnemyType.h"
#include "BulletActor.h"
#include "ofApp.h"

Result BattleState::result = Result::NONE;
queue<int> BattleState::m_attackQueue;

void InitBattleState::enter(BattleComponent * _battleComponent)
{
	result = Result::NONE;
	while (!m_attackQueue.empty())
	{
		m_attackQueue.pop();
	}
}

BattleState * InitBattleState::update(BattleComponent * _battleComponent)
{
	return new JudgeState();
}

void InitBattleState::exit(BattleComponent * _battleComponent)
{
}

void SelectCommandState::enter(BattleComponent * _battleComponent)
{
}

BattleState * SelectCommandState::update(BattleComponent * _battleComponent)
{
	bool down = ofApp::getInstance()->mp_inputManager->getButtonDown("Down");
	bool up = ofApp::getInstance()->mp_inputManager->getButtonDown("Up");

	// 選択
	if (down)
	{
		if (++m_bulletTypeIndex >= static_cast<int>(BulletType::TypeNum))
		{
			m_bulletTypeIndex = 0;
		}
		string bulletInfo = "Select:";
		bulletInfo.append(BulletComponent::getBullet(static_cast<BulletType>(m_bulletTypeIndex)).bulletName.c_str());
		OutputDebugStringA(bulletInfo.append("\n").c_str());
	}
	else if (up)
	{
		if (--m_bulletTypeIndex < 0)
		{
			m_bulletTypeIndex = static_cast<int>(BulletType::TypeNum) - 1;
		}
		string bulletInfo = "Select:";
		bulletInfo.append(BulletComponent::getBullet(static_cast<BulletType>(m_bulletTypeIndex)).bulletName.c_str());
		OutputDebugStringA(bulletInfo.append("\n").c_str());
	}

	// 決定
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start"))
	{
		auto state = new AttackState();
		state->initialize(0, 1, static_cast<BulletType>(m_bulletTypeIndex));
		return state;
	}

	return nullptr;
}

void SelectCommandState::exit(BattleComponent * _battleComponent)
{
}

void JudgeState::enter(BattleComponent * _battleComponent)
{
	int pHP = _battleComponent->GetPlayer()->getPlayerParam("HP");
	int eHP = _battleComponent->GetEnemyHp();

	if (pHP <= 0)
	{
		result = Result::LOSE;
	}
	else if (eHP <= 0)
	{
		result = Result::WIN;
	}
	else
	{
		result = Result::NONE;
	}
}

BattleState * JudgeState::update(BattleComponent * _battleComponent)
{
	switch (result)
	{
	case Result::NONE:
		return new TurnState();
		break;
	case Result::WIN:

		break;
	case Result::LOSE:

		break;
	default:
		break;
	}


	return nullptr;
}

void JudgeState::exit(BattleComponent * _battleComponent)
{
}

void GuardJudgeState::enter(BattleComponent * _battleComponent)
{
}

BattleState * GuardJudgeState::update(BattleComponent * _battleComponent)
{
	// 弾が全て消えたら遷移
	if (_battleComponent->GetBulletCount() == 0)
	{
		return new JudgeState();
	}

	return nullptr;
}

void GuardJudgeState::exit(BattleComponent * _battleComponent)
{
}

void TurnState::enter(BattleComponent * _battleComponent)
{
	// 空だったら、攻撃順を決定する
	if (m_attackQueue.empty())
	{
		m_attackQueue.push(0);
		m_attackQueue.push(1);
	}

	// 次行動するキャラ番号を取得
	m_turnIndex = m_attackQueue.front();
	m_attackQueue.pop();
}

BattleState * TurnState::update(BattleComponent * _battleComponent)
{
	if (m_turnIndex == 0)
	{
		return new SelectCommandState();
	}
	else
	{
		auto state = new AttackState();
		state->initialize(m_turnIndex, 0, BulletType::Nomal);
		return state;
	}

	return nullptr;
}

void TurnState::exit(BattleComponent * _battleComponent)
{
}

void AttackState::enter(BattleComponent * _battleComponent)
{
	// 弾アクター
	BulletActor* actor = nullptr;
	if (m_turnCharaIndex == 0)
	{
		actor = BulletActor::createPlayerBullet(_battleComponent->gActor(), _battleComponent->GetPlayerPos(), _battleComponent->GetEnemyPos(m_targetCharaIndex - 1), m_bulletType);
		//for (int i = 0; i < 3; ++i)
		//{
			auto actor1 = BulletActor::createPlayerBullet(_battleComponent->gActor(), _battleComponent->GetPlayerPos(), _battleComponent->GetEnemyPos(m_targetCharaIndex - 1), BulletType::Small);
			_battleComponent->AddBullet(actor1);
//		}
	}
	else
	{
		actor = BulletActor::createEnemyBullet(_battleComponent->gActor(), _battleComponent->GetEnemyPos(m_turnCharaIndex - 1), _battleComponent->GetPlayerPos(), m_bulletType);
	}

	// 作成したアクターを弾リストに追加
	_battleComponent->AddBullet(actor);
}

BattleState * AttackState::update(BattleComponent * _battleComponent)
{
	return new GuardJudgeState();
}

void AttackState::exit(BattleComponent * _battleComponent)
{
}

#include "ofApp.h"
#include "stdComponent.h"
#include "PlayerActor.h"
#include "EnemyActor.h"
#include "EnemyComponent.h"
#include "EnemyObject.h"
#include "EnemyType.h"
#include "BattleState.h"

BattleComponent::BattleComponent(GameActor* _gactor) :
	Component(_gactor, "BattleComponent")
{
}

BattleComponent::~BattleComponent() {
	ofApp::getInstance()->mp_soundManager->stop(2);
}

void BattleComponent::update()
{
	static bool isAllMessageCheck = true;

	// コマンドが入っていない && 弾が全て削除済み
	if (!m_commandList.empty() && m_bulletList.empty()) {
		ExcuteCommand();
		isAllMessageCheck = false;
	}
	else if (!m_messageList.empty()) {
		// 決定
		if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
			m_stateInfo = m_messageList.front();
			m_messageList.pop();
			isAllMessageCheck = false;
		}
	}
	else {
		auto state = mp_battleState->update(this);
		if (state) {
			mp_battleState->exit(this);
			mp_battleState.reset(state);
			mp_battleState->enter(this);
		}
	}
}

void BattleComponent::input()
{
}

void BattleComponent::Initialize(const bool _isBossBattle)
{
	// ボス戦かどうか設定
	m_isBossBattle = _isBossBattle;

	// 背景
	auto spriteCpnt = mp_gActor->addComponent<SpriteComponent>();
	spriteCpnt->initialize("backGround_map_1.png");

	//BGM
	ofApp::getInstance()->mp_soundManager->setVolume(2, 0.4f);
	ofApp::getInstance()->mp_soundManager->loop(2);

	// プレイヤー
	mp_charaActor = PlayerActor::createPlayer(mp_gActor, { Define::FULLWIN_W * 0.5f, Define::FULLWIN_H * 0.9f }, this);

	// アイテムコンポーネント
	mp_gActor->addComponent<ItemComponent>();

	// 敵
	InitEnemyList();
	// 戦闘状態の初期化
	mp_battleState = make_unique<InitBattleState>();
	mp_battleState->enter(this);

	// 弾マップの初期化
	BulletComponent::InitBulletMap();

	m_stateInfo = u8"戦闘開始\n";
}

void BattleComponent::AddBullet(GameActor * _bulletActor)
{
	_bulletActor->getComponent<BulletComponent>()->SetBattleComponent(this);
	m_bulletList.emplace_back(_bulletActor);
}

void BattleComponent::DeleteBullet(GameActor * _bulletActor)
{
	auto res = find_if(m_bulletList.begin(), m_bulletList.end(),
		[&](const auto& c) {return c == _bulletActor; });
	if (res != m_bulletList.end()) {
		m_bulletList.erase(res);
	}
}

void BattleComponent::AddCommand(unique_ptr<Command>&& _command)
{
	m_commandList.push(move(_command));
}

void BattleComponent::DeleteEnemy(GameActor * _actor)
{
	auto res = find_if(m_EnemyList.begin(), m_EnemyList.end(),
		[&](const auto& c) {return c == _actor; });
	if (res != m_EnemyList.end()) {
		m_EnemyList.erase(res);
	}

	auto attackRes = find_if(m_attackList.begin(), m_attackList.end(),
		[&](const auto& c) {return c == _actor; });
	if (attackRes != m_attackList.end()) {
		m_attackList.erase(attackRes);
	}
}

void BattleComponent::InitAttackOrder()
{
	// 空だったら、攻撃順を決定する
	if (m_attackList.empty())
	{
		// プレイヤー
		m_attackList.push_back(mp_charaActor);
		// 敵
		for (auto & enemy : m_EnemyList) {
			m_attackList.push_back(enemy);
		}

		// 素早さでソート（未実装）
		// std::sort(m_attackList.begin(), m_attackList.end(), []() {});
	}
}

Result BattleComponent::GetResult()
{
	if (!m_messageList.empty()) {
		return Result::NONE;
	}

	return mp_battleState->result;
}

void BattleComponent::ExcuteCommand()
{
	// 文字列初期化
	string message = m_commandList.front()->toName + u8"は";

	// コマンドタイプ
	const auto type = m_commandList.front()->commandType;

	// 合計値
	int sumVal = 0;
	while (!m_commandList.empty())
	{
		sumVal += m_commandList.front()->commandval;
		m_commandList.pop();
	}

	message += to_string(sumVal);
	if (type == 0) {
		message += u8"ダメージ受けた\n";
	}
	else {
		message += u8"回復した\n";
	}
	m_stateInfo = move(message);
}

void BattleComponent::InitEnemyList()
{
	EnemyActor* enemyActor = nullptr;

	if (true) {
		enemyActor = EnemyActor::createEnemy(mp_gActor, { Define::FULLWIN_W * 0.3f, Define::FULLWIN_H * 0.3f }, EnemyType::Nomal, this);
		//enemyActor = EnemyActor::createEnemy(mp_gActor, { Define::FULLWIN_W * 0.5f, Define::FULLWIN_H * 0.3f }, EnemyType::Boss, this);
		m_EnemyList.emplace_back(enemyActor);
		enemyActor = EnemyActor::createEnemy(mp_gActor, { Define::FULLWIN_W * 0.7f, Define::FULLWIN_H * 0.3f }, EnemyType::Nomal, this);
		//enemyActor = EnemyActor::createEnemy(mp_gActor, { Define::FULLWIN_W * 0.5f, Define::FULLWIN_H * 0.3f }, EnemyType::Boss, this);
		m_EnemyList.emplace_back(enemyActor);
	}
	else {
		const int enemyCount = rand() % 2 + 1;
		const float posRate = 1.f / (enemyCount + 1);
		for (int i = 1; i <= enemyCount; ++i) {
			auto enemyType = static_cast<EnemyType>(rand() % static_cast<int>(EnemyType::TYPE_NUM));
			enemyActor = EnemyActor::createEnemy(mp_gActor, { Define::FULLWIN_W * posRate * i,Define::FULLWIN_H * 0.3f }, enemyType, this);
			m_EnemyList.emplace_back(enemyActor);
		}
	}
}

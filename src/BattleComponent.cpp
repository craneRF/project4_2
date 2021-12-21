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
	// 背景
	auto spriteCpnt = mp_gActor->addComponent<SpriteComponent>();
	spriteCpnt->initialize("backGround_map_1.png");

	//BGM
	ofApp::getInstance()->mp_soundManager->setVolume(2, 0.4f);
	ofApp::getInstance()->mp_soundManager->loop(2);

	// プレイヤー
	{
		mp_charaActor = PlayerActor::createPlayer(_gactor, { Define::FULLWIN_W * 0.5f, Define::FULLWIN_H * 0.9f });
		mp_charaActor->getComponent<BoxComponent>()->m_onCollisionFunc = [this](CollisionComponent* _other)
		{
			auto res = find_if(m_bulletList.begin(), m_bulletList.end(),
				[&](const auto& c) {return c == _other->gActor(); });

			// 相手が弾リストに入っていたら、弾のダメージを取得して、コマンドを作成する
			if (res != m_bulletList.end())
			{
				int damage = BulletComponent::getBullet((*res)->getComponent<BulletComponent>()->getBulletType()).damage * 3;
				int hp = mp_Player->getPlayerParam("HP") - damage;
				mp_Player->setPlayerParam("HP", hp);

				m_commandList.push(make_unique<Command>(_other->gActor()->Name(), mp_charaActor->Name(), 0, damage));

				cout << "ガード判定：本体の範囲で押されました。\n";
				_other->gActor()->StateErace();
				m_bulletList.erase(res);

			}
		};

		auto imageSize = mp_charaActor->getComponent<PlayerComponent>()->GetImageSize();
		ofVec3f incrementSize = imageSize * 0.3f;
		imageSize *= 0.4f;
		// ガード判定
		for (int i = 1; i <= 2; ++i)
		{
			auto boxComp = mp_charaActor->addComponent<BoxComponent>();
			boxComp->initialize({ 0,0 }, imageSize.x + i * incrementSize.x, imageSize.y + i * incrementSize.y, CollisionType::PLAYER_OBJECT);
			boxComp->m_onCollisionFunc = [this, i](CollisionComponent* _other)
			{
				if (ofApp::getInstance()->mp_inputManager->getButtonDown("Fire"))
				{
					// 当たった相手が弾リストに入っているか確認
					auto res = find_if(m_bulletList.begin(), m_bulletList.end(),
						[&](const auto& c) {return c == _other->gActor(); });

					// 相手が弾リストに入っていたら、弾のダメージを取得して、コマンドを作成する
					if (res != m_bulletList.end())
					{
						int damage = BulletComponent::getBullet((*res)->getComponent<BulletComponent>()->getBulletType()).damage * i;
						int hp = mp_Player->getPlayerParam("HP") - damage;
						mp_Player->setPlayerParam("HP", hp);
						m_commandList.push(make_unique<Command>(_other->gActor()->Name(), mp_charaActor->Name(), 0, damage));
						cout << "ガード判定：" << to_string(i) << "ダメージの範囲で押されました。\n";
						_other->gActor()->StateErace();
						m_bulletList.erase(res);
					}
				}
			};
		}
	}

	// 敵
	InitEnemyList();
	// 戦闘状態の初期化
	mp_battleState = make_unique<InitBattleState>();
	mp_battleState->enter(this);
}

BattleComponent::~BattleComponent() {

}

void BattleComponent::update()
{
	static int count = 0;
	// コマンドが入っている && 弾が全て削除済み
	if (!m_commandList.empty() && m_bulletList.empty())
	{
		ExcuteCommand();
	}
	else
	{
		auto state = mp_battleState->update(this);
		if (state)
		{
			mp_battleState->exit(this);
			mp_battleState.reset(state);
			mp_battleState->enter(this);

			++count;
			string info = typeid(*mp_battleState).name() + to_string(count);
			OutputDebugStringA(info.append("\n").c_str());
		}
	}
}

void BattleComponent::input()
{
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
}

Result BattleComponent::GetResult()
{
	return mp_battleState->result;
}

void BattleComponent::ExcuteCommand()
{
	// 文字列初期化
	m_stateInfo = m_commandList.front()->fromName + u8"が" + m_commandList.front()->toName;

	// コマンドタイプ
	const auto type = m_commandList.front()->commandType;

	// 合計値
	int sumVal = 0;
	while (!m_commandList.empty())
	{
		sumVal += m_commandList.front()->commandval;
		m_commandList.pop();
	}


	if (type == 0) {
		m_stateInfo += u8"に" + to_string(sumVal) + u8"ダメージを与えた\n";
	}
	else {
		m_stateInfo += u8"を" + to_string(sumVal) + u8"回復させた\n";
	}
}

void BattleComponent::InitEnemyList()
{
	auto enemyActor = EnemyActor::createEnemy(mp_gActor, { Define::FULLWIN_W * 0.5f,Define::FULLWIN_H * 0.3f }, EnemyType::Nomal, this);
	m_EnemyList.emplace_back(enemyActor);
}

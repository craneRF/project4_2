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

	// プレイヤー
	{
		mp_charaActor = PlayerActor::createPlayer(_gactor, { Define::FULLWIN_W * 3 / 4.f, Define::FULLWIN_H * 1.f / 4 });
		mp_charaActor->getComponent<CollisionComponent>()->m_onCollisionFunc = [this](CollisionComponent* _other)
		{
			if (_other->gActor()->GetActorState() == Actor::ActorState::EErace)
			{
				return;
			}
			if (mp_Command)
			{
				return;
			}

			auto res = find_if(m_bulletList.begin(), m_bulletList.end(),
				[&](const auto& c) {return c == _other->gActor(); });

			// 相手が弾リストに入っていたら、弾のダメージを取得して、コマンドを作成する
			if (res != m_bulletList.end())
			{
				int damage = BulletComponent::getBullet((*res)->getComponent<BulletComponent>()->getBulletType()).damage;
				mp_Command.reset(new Command());
				mp_Command->fromIndex = 1;
				mp_Command->toIndex = 0;
				mp_Command->commandType = 0;
				mp_Command->commandval = 3 * damage;

				// 当たった弾をリストから削除
				m_bulletList.erase(res);

				cout << "ガード判定：" << "本体の範囲で押されました。\n";
				_other->gActor()->StateErace();
			}
		};

		auto imageSize = mp_charaActor->getComponent<PlayerComponent>()->GetImageSize() * 0.6f;
		ofVec3f incrementSize = imageSize * 0.2f;
		for (int i = 1; i <= 2; ++i)
		{
			auto collisionComp = mp_charaActor->addComponent<CollisionComponent>();
			collisionComp->initialize({ 0,0 }, imageSize.x + i * incrementSize.x, imageSize.y + i * incrementSize.y, CollisionType::PLAYER_OBJECT);
			collisionComp->m_onCollisionFunc = [this, i](CollisionComponent* _other)
			{
				if (_other->gActor()->GetActorState() == Actor::ActorState::EErace)
				{
					return;
				}
				if (mp_Command)
				{
					return;
				}

				if (ofApp::getInstance()->mp_inputManager->getButtonDown("Fire"))
				{
					// 当たった相手が弾リストに入っているか確認
					auto res = find_if(m_bulletList.begin(), m_bulletList.end(),
						[&](const auto& c) {return c == _other->gActor(); });

					// 相手が弾リストに入っていたら、弾のダメージを取得して、コマンドを作成する
					if (res != m_bulletList.end())
					{
						int damage = BulletComponent::getBullet((*res)->getComponent<BulletComponent>()->getBulletType()).damage;

						// 当たった弾をリストから削除
						m_bulletList.erase(res);

						mp_Command.reset(new Command());
						mp_Command->fromIndex = 1;
						mp_Command->toIndex = 0;
						mp_Command->commandType = 0;
						mp_Command->commandval = i * damage;

						cout << "ガード判定：" << to_string(i) << "ダメージの範囲で押されました。\n";
						_other->gActor()->StateErace();
					}
				}
			};
		}
	}

	// 敵
	InitEnemyList();

	mp_battleState = make_unique<InitBattleState>();
	mp_battleState->enter(this);
}

BattleComponent::~BattleComponent() {

}

void BattleComponent::update(float _deltatime)
{
	static int count = 0;
	if (mp_Command)
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

void BattleComponent::input(float _deltatime)
{
}

Result BattleComponent::GetResult()
{
	return mp_battleState->result;
}

void BattleComponent::ExcuteCommand()
{
	// 変化させるHP
	int hp = 0;
	// 文字列初期化
	m_stateInfo = "";
	// だれが
	if (mp_Command->fromIndex == 0) {
		m_stateInfo += u8"プレイヤーが";
	}
	else {
		m_stateInfo += u8"エネミーが";
	}

	// だれに
	if (mp_Command->toIndex == 0) {
		m_stateInfo += u8"プレイヤーのHPを";
		hp = mp_Player->getPlayerParam("HP");
	}
	else {
		m_stateInfo += u8"エネミーのHPを";
		hp = m_EnemyHP;
	}

	// 何をした
	m_stateInfo += to_string(mp_Command->commandval);
	if (mp_Command->commandType == 0) {
		m_stateInfo += u8"減らした";
		mp_Command->commandval *= -1;
	}
	else {
		m_stateInfo += u8"回復させた";
	}

	// 数値処理
	hp += mp_Command->commandval;

	//プレイヤーのHPの増減
	if (mp_Command->toIndex == 0) {
		mp_Player->setPlayerParam("HP", hp);
	}

	//敵のHPの増減
	if (mp_Command->toIndex == 1) {
		m_EnemyHP = hp;
	}
	//	現在のHP表示
	m_stateInfo += u8"\nエネミー：" + m_Enemyname + std::to_string(m_EnemyHP) + u8", プレイヤー：" + std::to_string(mp_Player->getPlayerParam("HP"));


	// コマンドのリセット
	mp_Command.reset();
}

void BattleComponent::InitEnemyList()
{
	auto enemyActor = EnemyActor::createEnemy(mp_gActor, { Define::FULLWIN_W / 4.f * 1,Define::FULLWIN_H * 3 / 4.f }, EnemyType::Nomal);
	m_EnemyList.emplace_back(enemyActor);

	auto enemyCpnt = enemyActor->getComponent<EnemyComponent>();
	m_EnemyHP = enemyCpnt->getEnemy(Nomal).HP;
	m_Enemyname = m_EnemyList[0]->getEnemyName();

	for (auto& enemy : m_EnemyList)
	{
		enemy->getComponent<CollisionComponent>()->m_onCollisionFunc = [this](CollisionComponent* _other) {
			// 当たった相手が弾リストに入っているか確認
			auto res = find_if(m_bulletList.begin(), m_bulletList.end(),
				[&](const auto& c) {return c == _other->gActor(); });

			// 相手が弾リストに入っていたら、弾のダメージを取得して、コマンドを作成する
			if (res != m_bulletList.end())
			{
				int damage = BulletComponent::getBullet((*res)->getComponent<BulletComponent>()->getBulletType()).damage;

				// 当たった弾をリストから削除
				m_bulletList.erase(res);

				mp_Command.reset(new Command());
				mp_Command->fromIndex = 0;
				mp_Command->toIndex = 1;
				mp_Command->commandType = 0;
				mp_Command->commandval = damage;

				cout << "敵に当たりました。\n";
				_other->gActor()->StateErace();
			}
		};
	}
}

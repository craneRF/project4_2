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
				int damage = BulletComponent::getBullet((*res)->getComponent<BulletComponent>()->getBulletType()).damage;

				m_commandList.push(make_unique<Command>(1, 0, 0, 3 * damage));

				cout << "ガード判定：本体の範囲で押されました。\n";
				_other->gActor()->StateErace();
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
						int damage = BulletComponent::getBullet((*res)->getComponent<BulletComponent>()->getBulletType()).damage;

						m_commandList.push(make_unique<Command>(1, 0, 0, i * damage));

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

	int toIndex = m_commandList.front()->toIndex;
	int fromIndex = m_commandList.front()->fromIndex;
	int commandType = m_commandList.front()->commandType;

	// だれが
	if (fromIndex == 0) {
		m_stateInfo += u8"プレイヤーが";
	}
	else {
		m_stateInfo += u8"エネミーが";
	}

	// だれに
	if (toIndex == 0) {
		m_stateInfo += u8"プレイヤーのHPを";
		hp = mp_Player->getPlayerParam("HP");
	}
	else {
		m_stateInfo += u8"エネミーのHPを";
		hp = m_EnemyHP;
	}

	// 何をした
	// 合計値
	int sumVal = 0;
	while (!m_commandList.empty())
	{
		sumVal += m_commandList.front()->commandval;
		m_commandList.pop();
	}
	m_stateInfo += to_string(sumVal);
	if (commandType == 0) {
		m_stateInfo += u8"減らした";
		sumVal *= -1;
	}
	else {
		m_stateInfo += u8"回復させた";
	}

	// 数値処理
	hp += sumVal;

	//プレイヤーのHPの増減
	if (toIndex == 0) {
		mp_Player->setPlayerParam("HP", hp);
	}
	//敵のHPの増減
	else{
		m_EnemyHP = hp;
	}
	//	現在のHP表示
	m_stateInfo += u8"\nエネミー：" + m_Enemyname + std::to_string(m_EnemyHP) + u8", プレイヤー：" + std::to_string(mp_Player->getPlayerParam("HP"));


}

void BattleComponent::InitEnemyList()
{
	auto enemyActor = EnemyActor::createEnemy(mp_gActor, { Define::FULLWIN_W * 0.5f,Define::FULLWIN_H * 0.3f }, EnemyType::Nomal);
	m_EnemyList.emplace_back(enemyActor);

	auto enemyCpnt = enemyActor->getComponent<EnemyComponent>();
	m_EnemyHP = enemyCpnt->getEnemy(Nomal).HP;
	m_Enemyname = m_EnemyList[0]->getEnemyName();

	for (auto& enemy : m_EnemyList)
	{
		enemy->getComponent<BoxComponent>()->m_onCollisionFunc = [this](CollisionComponent* _other) {
			// 当たった相手が弾リストに入っているか確認
			auto res = find_if(m_bulletList.begin(), m_bulletList.end(),
				[&](const auto& c) {return c == _other->gActor(); });

			// 相手が弾リストに入っていたら、弾のダメージを取得して、コマンドを作成する
			if (res != m_bulletList.end())
			{
				int damage = BulletComponent::getBullet((*res)->getComponent<BulletComponent>()->getBulletType()).damage;
				int playerAttack = mp_Player->getPlayerParam("ATTACK");

				m_commandList.push(make_unique<Command>(0, 1, 0, damage * playerAttack));

				cout << "敵に当たりました。\n";
				_other->gActor()->StateErace();
			}
		};
	}
}
//#include "ofApp.h"
//#include "stdComponent.h"
//#include "PlayerActor.h"
//#include "EnemyActor.h"
//#include "EnemyComponent.h"
//#include "EnemyObject.h"
//#include "EnemyType.h"
//#include "BattleState.h"
//
//BattleComponent::BattleComponent(GameActor* _gactor) :
//	Component(_gactor, "BattleComponent")
//{
//	// 背景
//	auto spriteCpnt = mp_gActor->addComponent<SpriteComponent>();
//	spriteCpnt->initialize("backGround_map_1.png");
//
//	//BGM
//	ofApp::getInstance()->mp_soundManager->setVolume(2, 0.4f);
//	ofApp::getInstance()->mp_soundManager->loop(2);
//
//	// プレイヤー
//	{
//		mp_charaActor = PlayerActor::createPlayer(_gactor, { Define::FULLWIN_W * 0.5f, Define::FULLWIN_H * 0.9f });
//		mp_charaActor->getComponent<BoxComponent>()->m_onCollisionFunc = [this](CollisionComponent* _other)
//		{
//			auto res = find_if(m_bulletList.begin(), m_bulletList.end(),
//				[&](const auto& c) {return c == _other->gActor(); });
//
//			// 相手が弾リストに入っていたら、弾のダメージを取得して、コマンドを作成する
//			if (res != m_bulletList.end())
//			{
//				int damage = BulletComponent::getBullet((*res)->getComponent<BulletComponent>()->getBulletType()).damage;
//
//				m_commandList.push(make_unique<Command>(1, 0, 0, 3 * damage));
//
//				cout << "ガード判定：本体の範囲で押されました。\n";
//				_other->gActor()->StateErace();
//			}
//		};
//
//		auto imageSize = mp_charaActor->getComponent<PlayerComponent>()->GetImageSize();
//		ofVec3f incrementSize = imageSize * 0.3f;
//		imageSize *= 0.4f;
//		// ガード判定
//		for (int i = 1; i <= 2; ++i)
//		{
//			auto boxComp = mp_charaActor->addComponent<BoxComponent>();
//			boxComp->initialize({ 0,0 }, imageSize.x + i * incrementSize.x, imageSize.y + i * incrementSize.y, CollisionType::PLAYER_OBJECT);
//			boxComp->m_onCollisionFunc = [this, i](CollisionComponent* _other)
//			{
//				if (ofApp::getInstance()->mp_inputManager->getButtonDown("Fire"))
//				{
//					// 当たった相手が弾リストに入っているか確認
//					auto res = find_if(m_bulletList.begin(), m_bulletList.end(),
//						[&](const auto& c) {return c == _other->gActor(); });
//
//					// 相手が弾リストに入っていたら、弾のダメージを取得して、コマンドを作成する
//					if (res != m_bulletList.end())
//					{
//						int damage = BulletComponent::getBullet((*res)->getComponent<BulletComponent>()->getBulletType()).damage;
//
//						m_commandList.push(make_unique<Command>(1, 0, 0, i * damage));
//
//						cout << "ガード判定：" << to_string(i) << "ダメージの範囲で押されました。\n";
//						_other->gActor()->StateErace();
//					}
//				}
//			};
//		}
//	}
//
//	// 敵
//	InitEnemyList();
//
//	mp_battleState = make_unique<InitBattleState>();
//	mp_battleState->enter(this);
//}
//
//BattleComponent::~BattleComponent() {
//
//}
//
//void BattleComponent::update()
//{
//	static int count = 0;
//	if (!m_commandList.empty())
//	{
//		ExcuteCommand(m_commandList.front().get());
//		// m_commandList.pop();
//	}
//	else
//	{
//		auto state = mp_battleState->update(this);
//		if (state)
//		{
//			mp_battleState->exit(this);
//			mp_battleState.reset(state);
//			mp_battleState->enter(this);
//
//			++count;
//			string info = typeid(*mp_battleState).name() + to_string(count);
//			OutputDebugStringA(info.append("\n").c_str());
//		}
//	}
//}
//
//void BattleComponent::input()
//{
//}
//
//Result BattleComponent::GetResult()
//{
//	return mp_battleState->result;
//}
//
//void BattleComponent::ExcuteCommand(Command* _command)
//{
//	// 変化させるHP
//	int hp = 0;
//	// 文字列初期化
//	m_stateInfo = "";
//
//	// だれが
//	if (_command->fromIndex == 0) {
//		m_stateInfo += u8"プレイヤーが";
//	}
//	else {
//		m_stateInfo += u8"エネミーが";
//	}
//
//	// だれに
//	if (_command->toIndex == 0) {
//		m_stateInfo += u8"プレイヤーのHPを";
//		hp = mp_Player->getPlayerParam("HP");
//	}
//	else {
//		m_stateInfo += u8"エネミーのHPを";
//		hp = m_EnemyHP;
//	}
//
//	// 何をした
//	m_stateInfo += to_string(_command->commandval);
//	if (_command->commandType == 0) {
//		m_stateInfo += u8"減らした";
//		_command->commandval *= -1;
//	}
//	else {
//		m_stateInfo += u8"回復させた";
//	}
//
//	// 数値処理
//	hp += _command->commandval;
//
//	//プレイヤーのHPの増減
//	if (_command->toIndex == 0) {
//		mp_Player->setPlayerParam("HP", hp);
//	}
//
//	//敵のHPの増減
//	if (_command->toIndex == 1) {
//		m_EnemyHP = hp;
//	}
//	//	現在のHP表示
//	m_stateInfo += u8"\nエネミー：" + m_Enemyname + std::to_string(m_EnemyHP) + u8", プレイヤー：" + std::to_string(mp_Player->getPlayerParam("HP"));
//}
//
//void BattleComponent::InitEnemyList()
//{
//	auto enemyActor = EnemyActor::createEnemy(mp_gActor, { Define::FULLWIN_W * 0.5f,Define::FULLWIN_H * 0.3f }, EnemyType::Nomal);
//	m_EnemyList.emplace_back(enemyActor);
//
//	auto enemyCpnt = enemyActor->getComponent<EnemyComponent>();
//	m_EnemyHP = enemyCpnt->getEnemy(Nomal).HP;
//	m_Enemyname = m_EnemyList[0]->getEnemyName();
//
//	for (auto& enemy : m_EnemyList)
//	{
//		enemy->getComponent<BoxComponent>()->m_onCollisionFunc = [this](CollisionComponent* _other) {
//			// 当たった相手が弾リストに入っているか確認
//			auto res = find_if(m_bulletList.begin(), m_bulletList.end(),
//				[&](const auto& c) {return c == _other->gActor(); });
//
//			// 相手が弾リストに入っていたら、弾のダメージを取得して、コマンドを作成する
//			if (res != m_bulletList.end())
//			{
//				int damage = BulletComponent::getBullet((*res)->getComponent<BulletComponent>()->getBulletType()).damage;
//				int playerAttack = mp_Player->getPlayerParam("ATTACK");
//
//				m_commandList.push(make_unique<Command>(0, 1, 0, damage * playerAttack));
//
//				cout << "敵に当たりました。\n";
//				_other->gActor()->StateErace();
//			}
//		};
//	}
//}


#include "stdComponent.h"
#include "PlayerActor.h"
#include "EnemyActor.h"
#include "ofApp.h"
#include "EnemyComponent.h"
#include "EnemyObject.h"
#include "EnemyType.h"

BattleComponent::BattleComponent(GameActor* _gactor) :
	Component(_gactor, "BattleComponent")
{
	m_EnemyList.reserve(2);
	auto charaActor = PlayerActor::createPlayer(_gactor, { 500, 500 });
	charaActor->getComponent<CollisionComponent>()->m_onCollisionFunc = [&](CollisionComponent* _other)
	{
		if (_other->gActor()->waitforErase_)
		{
			return;
		}
		if (mp_Command)
		{
			return;
		}

		cout << "ガード判定：" << "本体の範囲で押されました。\n";
		_other->gActor()->waitforErase_ = true;

		//mp_Command.reset();
		mp_Command = make_unique<Command>();
		mp_Command->fromIndex = 1;
		mp_Command->toIdenx = 0;
		mp_Command->commandType = 0;
		mp_Command->commandval = 3;
	};

	m_EnemyList.emplace_back(charaActor);
	for (int i = 1; i <= 2; ++i)
	{
		auto collisionComp = charaActor->addComponent<CollisionComponent>();
		collisionComp->initialize({ 0,0 }, 2067 + i * 300, 2067 + i * 300, CollisionType::PLAYER_OBJECT);
		collisionComp->m_onCollisionFunc = [&, i](CollisionComponent* _other)
		{
			if (_other->gActor()->waitforErase_)
			{
				return;
			}
			if (mp_Command)
			{
				return;
			}

			if (ofApp::getInstance()->mp_inputManager->getButtonDown("Fire"))
			{
				cout << "ガード判定：" << to_string(i) << "ダメージの範囲で押されました。\n";
				_other->gActor()->waitforErase_ = true;

				//mp_Command.reset();
				mp_Command = make_unique<Command>();
				mp_Command->fromIndex = 1;
				mp_Command->toIdenx = 0;
				mp_Command->commandType = 0;
				mp_Command->commandval = i;

			}
		};
	}
	m_EnemyList.emplace_back(EnemyActor::createEnemy(_gactor, { 200, 200 }));
}

BattleComponent::~BattleComponent() {

}

void BattleComponent::update(float _deltatime)
{
	if (m_result != Result::NONE) {
		return;
	}

	bool start = ofApp::getInstance()->mp_inputManager->getButtonDown("Start");
	// 決定
	if (start)
	{
		if (!m_IsStart) {
			m_IsStart = true;
			return;
		}

		// 速さ
		float speed = 50.f;
		// ベクトル作成
		ofVec3f direction = m_EnemyList[1]->Pos() - m_EnemyList[0]->Pos();
		// 正規化
		direction.normalize();
		ofVec3f forward = { 0, -1 };
		// 回転
		float angle = ofRadToDeg(acosf(direction.dot(forward)));

		// 攻撃アクター
		GameActor* actor = nullptr;
		if (/*mp_Command->fromIndex == 0*/false)
		{
			// 攻撃アクター作成
			actor = PlayerActor::createPlayer(mp_gActor, m_EnemyList[0]->Pos());
			// 回転設定
			actor->RotAngle() = angle;
			// 速さ設定
			direction *= speed;
		}
		else
		{
			actor = EnemyActor::createEnemy(mp_gActor, m_EnemyList[1]->Pos());
			actor->RotAngle() = angle + 180;
			direction *= -speed;
			// エネミーアクターはMoveComponentがなかったため、ここで付ける
			actor->addComponent<MoveComponent>();
		}
		// 方向設定
		actor->getComponent<MoveComponent>()->setMoveVec(direction);
		// サイズを本体の1/5に
		actor->Scale() *= 0.2f;

	}


	ExcuteCommand();
	CheckResult();
//void BattleComponent::SetEnemy(vector <EnemyActor*> _enemyList)
//{
//	m_EnemyList = _enemyList;
//	auto enemyCpnt = m_EnemyList[0]->getComponent<EnemyComponent>();
//	m_EnemyHP = enemyCpnt->getEnemy(Nomal).HP;
//	m_Enemyname = _enemyList[Nomal]->getEnemyName();
//}


void BattleComponent::CheckResult()
{
	if (m_Player->getPlayerParam("HP") <= 0)
	{
		m_result = Result::LOSE;
	}
	else if (m_EnemyHP <= 0)
		//else if (m_EnemyList.size() <= 0)
	{
		m_result = Result::WIN;
	}
	else {
		m_result = Result::NONE;
	}
}

void BattleComponent::ExcuteCommand()
{
	// コマンドがなければ何もしない
	if (!mp_Command)
	{
		return;
	}

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
	if (mp_Command->toIdenx == 0) {
		m_stateInfo += u8"プレイヤーのHPを";
		hp = m_Player->getPlayerParam("HP");
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
	if (mp_Command->toIdenx == 0) {
		m_Player->setPlayerParam("HP", hp);
	}

	//敵のHPの増減
	if (mp_Command->toIdenx == 1) {
		m_EnemyHP = hp;
	}
	//	現在のHP表示
	m_stateInfo += u8"\nエネミー：" + m_Enemyname + std::to_string(m_EnemyHP) + u8", プレイヤー：" + std::to_string(m_Player->getPlayerParam("HP"));


	// コマンドのリセット
	mp_Command.reset();
}

#include "ofApp.h"
#include "stdComponent.h"
#include "PlayerActor.h"
#include "EnemyActor.h"
#include "EnemyComponent.h"
#include "EnemyObject.h"
#include "EnemyType.h"

BattleComponent::BattleComponent(GameActor* _gactor) :
	Component(_gactor, "BattleComponent")
{
	charaActor = PlayerActor::createPlayer(_gactor, { Define::FULLWIN_W / 2.f, Define::FULLWIN_H * 7.f / 8 });
	charaActor->getComponent<CollisionComponent>()->m_onCollisionFunc = [&](CollisionComponent* _other)
	{
		if (_other->gActor()->GetActorState() == Actor::ActorState::EErace)
		{
			return;
		}
		if (mp_Command)
		{
			return;
		}

		cout << "ガード判定：" << "本体の範囲で押されました。\n";
		_other->gActor()->StateErace();

		//mp_Command.reset();
		mp_Command = make_unique<Command>();
		mp_Command->fromIndex = 1;
		mp_Command->toIdenx = 0;
		mp_Command->commandType = 0;
		mp_Command->commandval = 3;
	};

	auto imageSize = charaActor->getComponent<PlayerComponent>()->GetImageSize() * 0.6f;
	ofVec3f incrementSize = imageSize * 0.2f;
	for (int i = 1; i <= 2; ++i)
	{
		auto collisionComp = charaActor->addComponent<CollisionComponent>();
		collisionComp->initialize({ 0,0 }, imageSize.x + i * incrementSize.x, imageSize.y + i * incrementSize.y, CollisionType::PLAYER_OBJECT);
		collisionComp->m_onCollisionFunc = [&, i](CollisionComponent* _other)
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
				cout << "ガード判定：" << to_string(i) << "ダメージの範囲で押されました。\n";
				_other->gActor()->StateErace();

				//mp_Command.reset();
				mp_Command = make_unique<Command>();
				mp_Command->fromIndex = 1;
				mp_Command->toIdenx = 0;
				mp_Command->commandType = 0;
				mp_Command->commandval = i;

			}
		};
	}

	auto spriteCpnt = mp_gActor->addComponent<SpriteComponent>();
	spriteCpnt->initialize("backGround.png");
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
		ofVec3f direction = charaActor->Pos() - m_EnemyList[0]->Pos();
		// 正規化
		direction.normalize();
		ofVec3f forward = { 1, 0 };
		// 回転
		float angle = ofRadToDeg(acosf(direction.dot(forward)));
		auto crossVec = forward.crossed(direction);
		if (crossVec.z > 0)
		{
			angle = 360 - angle;
		}
		angle = fmodf(angle, 360);

		// 攻撃アクター
		auto actor = EnemyActor::createEnemy(mp_gActor, m_EnemyList[0]->Pos(), EnemyType::Nomal);
		actor->RotAngle() = angle;
		auto sp = actor->getComponent<SpriteComponent>();
		sp->initialize("Arrow.png");
		sp->AlignPivotCenter();

		// エネミーアクターはMoveComponentがなかったため、ここで付ける
		actor->addComponent<MoveComponent>();

		// 方向設定
		auto moveCpnt = actor->getComponent<MoveComponent>();
		moveCpnt->AddMovePos(direction * speed);
		moveCpnt->m_isOnceMove = false;
	}


	ExcuteCommand();
	CheckResult();
}

void BattleComponent::input(float _deltatime)
{
}

//void BattleComponent::SetEnemy()
//{
//	auto enemyCpnt = m_EnemyList[1]->getComponent<EnemyComponent>();
//	m_EnemyHP = enemyCpnt->getEnemy(Nomal).HP;
//	m_Enemyname = "";
//	/*m_Enemyname = m_EnemyList[1]->getEnemyName();*/
//}

void BattleComponent::SetEnemy(vector <EnemyActor*> _enemyList)
{
	m_EnemyList = _enemyList;
	auto enemyCpnt = m_EnemyList[0]->getComponent<EnemyComponent>();
	m_EnemyHP = enemyCpnt->getEnemy(Nomal).HP;
	m_Enemyname = m_EnemyList[0]->getEnemyName();
}


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

#include "BattleComponent.h"
#include "GameActor.h"
#include "ofApp.h"
#include "EnemyComponent.h"
#include "EnemyObject.h"
#include "EnemyType.h"

BattleComponent::BattleComponent(GameActor* _gactor) :
	Component(_gactor, "BattleComponent") {

}

BattleComponent::~BattleComponent() {

}

void BattleComponent::update(float _deltatime)
{
	if (m_result != Result::NONE) {
		return;
	}
	if (mp_Command) {
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

		mp_Command = make_unique<Command>();
		switch (m_currentChara)
		{
		case 0:
			mp_Command->fromIndex = m_currentChara;
			mp_Command->toIdenx = 1;
			mp_Command->commandType = 0;
			mp_Command->commandval = 1;
			break;

		default:
			mp_Command->fromIndex = m_currentChara;
			mp_Command->toIdenx = 0;
			mp_Command->commandType = 0;
			mp_Command->commandval = 1;
			break;
		}

		++m_currentChara;
		if (m_currentChara > m_EnemyList.size())
		{
			m_currentChara = 0;
		}
	}
	ExcuteCommand();
	CheckResult();
}

void BattleComponent::SetEnemy(vector <EnemyActor*> _enemyList)
{
	m_EnemyList = _enemyList;
	auto enemyCpnt = m_EnemyList[0]->getComponent<EnemyComponent>();
	m_EnemyHP = enemyCpnt->getEnemy(Nomal).HP;
	m_Enemyname = _enemyList[Nomal]->getEnemyName();
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

	// 変化させるHPのポインタ
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

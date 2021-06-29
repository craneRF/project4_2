
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

		cout << "�K�[�h����F" << "�{�͈̂̔͂ŉ�����܂����B\n";
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
				cout << "�K�[�h����F" << to_string(i) << "�_���[�W�͈̔͂ŉ�����܂����B\n";
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
	// ����
	if (start)
	{
		if (!m_IsStart) {
			m_IsStart = true;
			return;
		}

		// ����
		float speed = 50.f;
		// �x�N�g���쐬
		ofVec3f direction = m_EnemyList[1]->Pos() - m_EnemyList[0]->Pos();
		// ���K��
		direction.normalize();
		ofVec3f forward = { 0, -1 };
		// ��]
		float angle = ofRadToDeg(acosf(direction.dot(forward)));

		// �U���A�N�^�[
		GameActor* actor = nullptr;
		if (/*mp_Command->fromIndex == 0*/false)
		{
			// �U���A�N�^�[�쐬
			actor = PlayerActor::createPlayer(mp_gActor, m_EnemyList[0]->Pos());
			// ��]�ݒ�
			actor->RotAngle() = angle;
			// �����ݒ�
			direction *= speed;
		}
		else
		{
			actor = EnemyActor::createEnemy(mp_gActor, m_EnemyList[1]->Pos());
			actor->RotAngle() = angle + 180;
			direction *= -speed;
			// �G�l�~�[�A�N�^�[��MoveComponent���Ȃ��������߁A�����ŕt����
			actor->addComponent<MoveComponent>();
		}
		// �����ݒ�
		actor->getComponent<MoveComponent>()->setMoveVec(direction);
		// �T�C�Y��{�̂�1/5��
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
	// �R�}���h���Ȃ���Ή������Ȃ�
	if (!mp_Command)
	{
		return;
	}

	// �ω�������HP
	int hp = 0;
	// �����񏉊���
	m_stateInfo = "";
	// ���ꂪ
	if (mp_Command->fromIndex == 0) {
		m_stateInfo += u8"�v���C���[��";
	}
	else {
		m_stateInfo += u8"�G�l�~�[��";
	}

	// �����
	if (mp_Command->toIdenx == 0) {
		m_stateInfo += u8"�v���C���[��HP��";
		hp = m_Player->getPlayerParam("HP");
	}
	else {
		m_stateInfo += u8"�G�l�~�[��HP��";
		hp = m_EnemyHP;
	}

	// ��������
	m_stateInfo += to_string(mp_Command->commandval);
	if (mp_Command->commandType == 0) {
		m_stateInfo += u8"���炵��";
		mp_Command->commandval *= -1;
	}
	else {
		m_stateInfo += u8"�񕜂�����";
	}

	// ���l����
	hp += mp_Command->commandval;

	//�v���C���[��HP�̑���
	if (mp_Command->toIdenx == 0) {
		m_Player->setPlayerParam("HP", hp);
	}

	//�G��HP�̑���
	if (mp_Command->toIdenx == 1) {
		m_EnemyHP = hp;
	}
	//	���݂�HP�\��
	m_stateInfo += u8"\n�G�l�~�[�F" + m_Enemyname + std::to_string(m_EnemyHP) + u8", �v���C���[�F" + std::to_string(m_Player->getPlayerParam("HP"));


	// �R�}���h�̃��Z�b�g
	mp_Command.reset();
}

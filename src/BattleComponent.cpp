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

		cout << "�K�[�h����F" << "�{�͈̂̔͂ŉ�����܂����B\n";
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
				cout << "�K�[�h����F" << to_string(i) << "�_���[�W�͈̔͂ŉ�����܂����B\n";
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
		ofVec3f direction = charaActor->Pos() - m_EnemyList[0]->Pos();
		// ���K��
		direction.normalize();
		ofVec3f forward = { 1, 0 };
		// ��]
		float angle = ofRadToDeg(acosf(direction.dot(forward)));
		auto crossVec = forward.crossed(direction);
		if (crossVec.z > 0)
		{
			angle = 360 - angle;
		}
		angle = fmodf(angle, 360);

		// �U���A�N�^�[
		auto actor = EnemyActor::createEnemy(mp_gActor, m_EnemyList[0]->Pos(), EnemyType::Nomal);
		actor->RotAngle() = angle;
		auto sp = actor->getComponent<SpriteComponent>();
		sp->initialize("Arrow.png");
		sp->AlignPivotCenter();

		// �G�l�~�[�A�N�^�[��MoveComponent���Ȃ��������߁A�����ŕt����
		actor->addComponent<MoveComponent>();

		// �����ݒ�
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

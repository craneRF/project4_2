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
	// �w�i
	auto spriteCpnt = mp_gActor->addComponent<SpriteComponent>();
	spriteCpnt->initialize("backGround_map_1.png");

	//BGM
	ofApp::getInstance()->mp_soundManager->setVolume(2, 0.4f);
	ofApp::getInstance()->mp_soundManager->loop(2);

	// �v���C���[
	{
		mp_charaActor = PlayerActor::createPlayer(_gactor, { Define::FULLWIN_W * 0.5f, Define::FULLWIN_H * 0.9f });
		mp_charaActor->getComponent<BoxComponent>()->m_onCollisionFunc = [this](CollisionComponent* _other)
		{
			auto res = find_if(m_bulletList.begin(), m_bulletList.end(),
				[&](const auto& c) {return c == _other->gActor(); });

			// ���肪�e���X�g�ɓ����Ă�����A�e�̃_���[�W���擾���āA�R�}���h���쐬����
			if (res != m_bulletList.end())
			{
				int damage = BulletComponent::getBullet((*res)->getComponent<BulletComponent>()->getBulletType()).damage;

				m_commandList.push(make_unique<Command>(1, 0, 0, 3 * damage));

				cout << "�K�[�h����F�{�͈̂̔͂ŉ�����܂����B\n";
				_other->gActor()->StateErace();
			}
		};

		auto imageSize = mp_charaActor->getComponent<PlayerComponent>()->GetImageSize();
		ofVec3f incrementSize = imageSize * 0.3f;
		imageSize *= 0.4f;
		// �K�[�h����
		for (int i = 1; i <= 2; ++i)
		{
			auto boxComp = mp_charaActor->addComponent<BoxComponent>();
			boxComp->initialize({ 0,0 }, imageSize.x + i * incrementSize.x, imageSize.y + i * incrementSize.y, CollisionType::PLAYER_OBJECT);
			boxComp->m_onCollisionFunc = [this, i](CollisionComponent* _other)
			{
				if (ofApp::getInstance()->mp_inputManager->getButtonDown("Fire"))
				{
					// �����������肪�e���X�g�ɓ����Ă��邩�m�F
					auto res = find_if(m_bulletList.begin(), m_bulletList.end(),
						[&](const auto& c) {return c == _other->gActor(); });

					// ���肪�e���X�g�ɓ����Ă�����A�e�̃_���[�W���擾���āA�R�}���h���쐬����
					if (res != m_bulletList.end())
					{
						int damage = BulletComponent::getBullet((*res)->getComponent<BulletComponent>()->getBulletType()).damage;

						m_commandList.push(make_unique<Command>(1, 0, 0, i * damage));

						cout << "�K�[�h����F" << to_string(i) << "�_���[�W�͈̔͂ŉ�����܂����B\n";
						_other->gActor()->StateErace();
					}
				}
			};
		}
	}

	// �G
	InitEnemyList();

	mp_battleState = make_unique<InitBattleState>();
	mp_battleState->enter(this);
}

BattleComponent::~BattleComponent() {

}

void BattleComponent::update()
{
	static int count = 0;
	// �R�}���h�������Ă��� && �e���S�č폜�ς�
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
	// �ω�������HP
	int hp = 0;
	// �����񏉊���
	m_stateInfo = "";

	int toIndex = m_commandList.front()->toIndex;
	int fromIndex = m_commandList.front()->fromIndex;
	int commandType = m_commandList.front()->commandType;

	// ���ꂪ
	if (fromIndex == 0) {
		m_stateInfo += u8"�v���C���[��";
	}
	else {
		m_stateInfo += u8"�G�l�~�[��";
	}

	// �����
	if (toIndex == 0) {
		m_stateInfo += u8"�v���C���[��HP��";
		hp = mp_Player->getPlayerParam("HP");
	}
	else {
		m_stateInfo += u8"�G�l�~�[��HP��";
		hp = m_EnemyHP;
	}

	// ��������
	// ���v�l
	int sumVal = 0;
	while (!m_commandList.empty())
	{
		sumVal += m_commandList.front()->commandval;
		m_commandList.pop();
	}
	m_stateInfo += to_string(sumVal);
	if (commandType == 0) {
		m_stateInfo += u8"���炵��";
		sumVal *= -1;
	}
	else {
		m_stateInfo += u8"�񕜂�����";
	}

	// ���l����
	hp += sumVal;

	//�v���C���[��HP�̑���
	if (toIndex == 0) {
		mp_Player->setPlayerParam("HP", hp);
	}
	//�G��HP�̑���
	else{
		m_EnemyHP = hp;
	}
	//	���݂�HP�\��
	m_stateInfo += u8"\n�G�l�~�[�F" + m_Enemyname + std::to_string(m_EnemyHP) + u8", �v���C���[�F" + std::to_string(mp_Player->getPlayerParam("HP"));


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
			// �����������肪�e���X�g�ɓ����Ă��邩�m�F
			auto res = find_if(m_bulletList.begin(), m_bulletList.end(),
				[&](const auto& c) {return c == _other->gActor(); });

			// ���肪�e���X�g�ɓ����Ă�����A�e�̃_���[�W���擾���āA�R�}���h���쐬����
			if (res != m_bulletList.end())
			{
				int damage = BulletComponent::getBullet((*res)->getComponent<BulletComponent>()->getBulletType()).damage;
				int playerAttack = mp_Player->getPlayerParam("ATTACK");

				m_commandList.push(make_unique<Command>(0, 1, 0, damage * playerAttack));

				cout << "�G�ɓ�����܂����B\n";
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
//	// �w�i
//	auto spriteCpnt = mp_gActor->addComponent<SpriteComponent>();
//	spriteCpnt->initialize("backGround_map_1.png");
//
//	//BGM
//	ofApp::getInstance()->mp_soundManager->setVolume(2, 0.4f);
//	ofApp::getInstance()->mp_soundManager->loop(2);
//
//	// �v���C���[
//	{
//		mp_charaActor = PlayerActor::createPlayer(_gactor, { Define::FULLWIN_W * 0.5f, Define::FULLWIN_H * 0.9f });
//		mp_charaActor->getComponent<BoxComponent>()->m_onCollisionFunc = [this](CollisionComponent* _other)
//		{
//			auto res = find_if(m_bulletList.begin(), m_bulletList.end(),
//				[&](const auto& c) {return c == _other->gActor(); });
//
//			// ���肪�e���X�g�ɓ����Ă�����A�e�̃_���[�W���擾���āA�R�}���h���쐬����
//			if (res != m_bulletList.end())
//			{
//				int damage = BulletComponent::getBullet((*res)->getComponent<BulletComponent>()->getBulletType()).damage;
//
//				m_commandList.push(make_unique<Command>(1, 0, 0, 3 * damage));
//
//				cout << "�K�[�h����F�{�͈̂̔͂ŉ�����܂����B\n";
//				_other->gActor()->StateErace();
//			}
//		};
//
//		auto imageSize = mp_charaActor->getComponent<PlayerComponent>()->GetImageSize();
//		ofVec3f incrementSize = imageSize * 0.3f;
//		imageSize *= 0.4f;
//		// �K�[�h����
//		for (int i = 1; i <= 2; ++i)
//		{
//			auto boxComp = mp_charaActor->addComponent<BoxComponent>();
//			boxComp->initialize({ 0,0 }, imageSize.x + i * incrementSize.x, imageSize.y + i * incrementSize.y, CollisionType::PLAYER_OBJECT);
//			boxComp->m_onCollisionFunc = [this, i](CollisionComponent* _other)
//			{
//				if (ofApp::getInstance()->mp_inputManager->getButtonDown("Fire"))
//				{
//					// �����������肪�e���X�g�ɓ����Ă��邩�m�F
//					auto res = find_if(m_bulletList.begin(), m_bulletList.end(),
//						[&](const auto& c) {return c == _other->gActor(); });
//
//					// ���肪�e���X�g�ɓ����Ă�����A�e�̃_���[�W���擾���āA�R�}���h���쐬����
//					if (res != m_bulletList.end())
//					{
//						int damage = BulletComponent::getBullet((*res)->getComponent<BulletComponent>()->getBulletType()).damage;
//
//						m_commandList.push(make_unique<Command>(1, 0, 0, i * damage));
//
//						cout << "�K�[�h����F" << to_string(i) << "�_���[�W�͈̔͂ŉ�����܂����B\n";
//						_other->gActor()->StateErace();
//					}
//				}
//			};
//		}
//	}
//
//	// �G
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
//	// �ω�������HP
//	int hp = 0;
//	// �����񏉊���
//	m_stateInfo = "";
//
//	// ���ꂪ
//	if (_command->fromIndex == 0) {
//		m_stateInfo += u8"�v���C���[��";
//	}
//	else {
//		m_stateInfo += u8"�G�l�~�[��";
//	}
//
//	// �����
//	if (_command->toIndex == 0) {
//		m_stateInfo += u8"�v���C���[��HP��";
//		hp = mp_Player->getPlayerParam("HP");
//	}
//	else {
//		m_stateInfo += u8"�G�l�~�[��HP��";
//		hp = m_EnemyHP;
//	}
//
//	// ��������
//	m_stateInfo += to_string(_command->commandval);
//	if (_command->commandType == 0) {
//		m_stateInfo += u8"���炵��";
//		_command->commandval *= -1;
//	}
//	else {
//		m_stateInfo += u8"�񕜂�����";
//	}
//
//	// ���l����
//	hp += _command->commandval;
//
//	//�v���C���[��HP�̑���
//	if (_command->toIndex == 0) {
//		mp_Player->setPlayerParam("HP", hp);
//	}
//
//	//�G��HP�̑���
//	if (_command->toIndex == 1) {
//		m_EnemyHP = hp;
//	}
//	//	���݂�HP�\��
//	m_stateInfo += u8"\n�G�l�~�[�F" + m_Enemyname + std::to_string(m_EnemyHP) + u8", �v���C���[�F" + std::to_string(mp_Player->getPlayerParam("HP"));
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
//			// �����������肪�e���X�g�ɓ����Ă��邩�m�F
//			auto res = find_if(m_bulletList.begin(), m_bulletList.end(),
//				[&](const auto& c) {return c == _other->gActor(); });
//
//			// ���肪�e���X�g�ɓ����Ă�����A�e�̃_���[�W���擾���āA�R�}���h���쐬����
//			if (res != m_bulletList.end())
//			{
//				int damage = BulletComponent::getBullet((*res)->getComponent<BulletComponent>()->getBulletType()).damage;
//				int playerAttack = mp_Player->getPlayerParam("ATTACK");
//
//				m_commandList.push(make_unique<Command>(0, 1, 0, damage * playerAttack));
//
//				cout << "�G�ɓ�����܂����B\n";
//				_other->gActor()->StateErace();
//			}
//		};
//	}
//}

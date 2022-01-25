#include "BattleState.h"
#include "stdComponent.h"
#include "EnemyObject.h"
#include "BulletActor.h"
#include "ofApp.h"
#include "ItemType.h"

Result BattleState::result = Result::NONE;

void InitBattleState::enter(BattleComponent * _battleComponent)
{
	result = Result::NONE;
}

BattleState * InitBattleState::update(BattleComponent * _battleComponent)
{
	return new JudgeState();
}

void InitBattleState::exit(BattleComponent * _battleComponent)
{
}

void SelectCommandState::enter(BattleComponent * _battleComponent)
{
	auto commandType = static_cast<CommandType>(m_commandInfo.commandTypeIndex);
	switch (commandType)
	{
	case BattleState::CommandType::SKILL:
		_battleComponent->AddMessage(string(u8"Select:�X�L��"));
		break;
	case BattleState::CommandType::ITEM:
		_battleComponent->AddMessage(string(u8"Select:�A�C�e��"));
		break;
	default:
		break;
	}
}

BattleState * SelectCommandState::update(BattleComponent * _battleComponent)
{
	bool down = ofApp::getInstance()->mp_inputManager->getButtonDown("Down");
	bool up = ofApp::getInstance()->mp_inputManager->getButtonDown("Up");

	//  �X�L�� or �A�C�e���I��
	if (!m_isSelectCommandType)
	{
		if (down)
		{
			ofApp::getInstance()->mp_soundManager->play(3);

			if (++m_commandInfo.commandTypeIndex >= static_cast<int>(CommandType::TYPE_NUM))
			{
				m_commandInfo.commandTypeIndex = 0;
			}
		}
		else if (up)
		{
			ofApp::getInstance()->mp_soundManager->play(3);

			if (--m_commandInfo.commandTypeIndex < 0)
			{
				m_commandInfo.commandTypeIndex = static_cast<int>(CommandType::TYPE_NUM) - 1;
			}
		}

		auto commandType = static_cast<CommandType>(m_commandInfo.commandTypeIndex);
		switch (commandType)
		{
		case BattleState::CommandType::SKILL:
			_battleComponent->SetMessage(string(u8"Select:�X�L��"));
			break;
		case BattleState::CommandType::ITEM:
			_battleComponent->SetMessage(string(u8"Select:�A�C�e��"));
			break;
		default:
			break;
		}

		// ����
		if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
			m_isSelectCommandType = true;
			ofApp::getInstance()->mp_soundManager->play(4);

			switch (commandType)
			{
			case BattleState::CommandType::SKILL:
				_battleComponent->SetMessage(u8"�X�L��:" + ofApp::getInstance()->mp_prm->GetSkillList().at(0).attackStatement);
				break;
			case BattleState::CommandType::ITEM:
			{
				auto itemCpnt = _battleComponent->gActor()->getComponent<ItemComponent>();
				_battleComponent->SetMessage(u8"�A�C�e��:" + itemCpnt->getItemName(0));
				break;
			}
			default:
				break;
			}
		}
		return nullptr;
	}

	if (!m_isSelectBulletType) {
		auto commandType = static_cast<CommandType>(m_commandInfo.commandTypeIndex);
		switch (commandType)
		{
		case BattleState::CommandType::SKILL:	// �X�L���I��
		{
			// �X�L�����X�g
			auto& skillList = ofApp::getInstance()->mp_prm->GetSkillList();

			if (down)
			{
				ofApp::getInstance()->mp_soundManager->play(3);

				if (++m_commandInfo.bulletTypeIndex >= skillList.size())
				{
					m_commandInfo.bulletTypeIndex = 0;
				}
				string bulletInfo = u8"�X�L��:";
				bulletInfo.append(skillList.at(m_commandInfo.bulletTypeIndex).attackStatement);
				_battleComponent->SetMessage(bulletInfo);
			}
			else if (up)
			{
				ofApp::getInstance()->mp_soundManager->play(3);

				if (--m_commandInfo.bulletTypeIndex < 0)
				{
					m_commandInfo.bulletTypeIndex = skillList.size() - 1;
				}
				string skillInfo = u8"�X�L��:";
				skillInfo.append(skillList.at(m_commandInfo.bulletTypeIndex).attackStatement);
				_battleComponent->SetMessage(move(skillInfo));
			}

			// ����
			if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
				m_isSelectBulletType = true;
				ofApp::getInstance()->mp_soundManager->play(4);
				string targetInfo = u8"�^�[�Q�b�g(�G):" + _battleComponent->GetEnemy(m_commandInfo.targetIndex)->Name();
				_battleComponent->SetMessage(move(targetInfo));
			}

			break;
		}
		case BattleState::CommandType::ITEM:	// �A�C�e��
		{
			auto itemCpnt = _battleComponent->gActor()->getComponent<ItemComponent>();
			static int itemIndex = 0;

			// �I��
			/*
			{
				if (down)
				{
					ofApp::getInstance()->mp_soundManager->play(3);

					if (++itemIndex >= ItemType::NumItems)
					{
						itemIndex = 0;
					}
					string itemInfo = u8"�A�C�e��:" + itemCpnt->getItemName(itemIndex);
					_battleComponent->SetMessage(move(itemInfo));
				}
				else if (up)
				{
					ofApp::getInstance()->mp_soundManager->play(3);

					if (--itemIndex < 0)
					{
						itemIndex = ItemType::NumItems - 1;
					}
					string itemInfo = u8"�A�C�e��:" + itemCpnt->getItemName(itemIndex);
					_battleComponent->SetMessage(move(itemInfo));
				}
			}
			*/

			// ����
			if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
				itemCpnt->useItem(ItemType::POTION);
				ofApp::getInstance()->mp_soundManager->play(4);
				_battleComponent->SetMessage(itemCpnt->getItem(ItemType::POTION).m_iParam.itemName + u8"���g�p����\n");
				return new JudgeState();
			}
			//if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
			//	itemCpnt->useItem(itemIndex);
			//	itemIndex = 0;
			//	ofApp::getInstance()->mp_soundManager->play(4);
			//	_battleComponent->SetMessage(itemCpnt->getItem(itemIndex).m_iParam.itemName + u8"���g�p����\n");
			//	return new JudgeState();
			//}

			break;
		}
		default:
			break;
		}

		return nullptr;
	}

	// �G�I��
	if (!m_isSelectTarget) {
		auto enemyCpnt = _battleComponent->GetEnemy(m_commandInfo.targetIndex)->getComponent<EnemyComponent>();
		// �F�ύX
		enemyCpnt->SetColor(ofColor::white);

		if (down)
		{
			ofApp::getInstance()->mp_soundManager->play(3);

			if (++m_commandInfo.targetIndex >= _battleComponent->GetEnemyCount())
			{
				m_commandInfo.targetIndex = 0;
			}

			string targetInfo = u8"�^�[�Q�b�g(�G):" + _battleComponent->GetEnemy(m_commandInfo.targetIndex)->Name();
			_battleComponent->SetMessage(move(targetInfo));
		}
		else if (up)
		{
			ofApp::getInstance()->mp_soundManager->play(3);

			if (--m_commandInfo.targetIndex < 0)
			{
				m_commandInfo.targetIndex = _battleComponent->GetEnemyCount() - 1;
			}

			string targetInfo = u8"�^�[�Q�b�g(�G):" + _battleComponent->GetEnemy(m_commandInfo.targetIndex)->Name();
			_battleComponent->SetMessage(move(targetInfo));
		}

		enemyCpnt = _battleComponent->GetEnemy(m_commandInfo.targetIndex)->getComponent<EnemyComponent>();
		// �F�ύX
		enemyCpnt->SetColor(ofColor::red);

		// ����
		if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")){
			m_isSelectTarget = true;
			ofApp::getInstance()->mp_soundManager->play(4);

			// �F�ύX
			enemyCpnt->SetColor(ofColor::white);

			string targetInfo = u8"�^�[�Q�b�g(����):" + enemyCpnt->GetPartsCpntList().at(m_commandInfo.partsIndex)->gActor()->Name();
			_battleComponent->SetMessage(move(targetInfo));
		}
		return nullptr;
	}

	// ���ʑI��
	if (!m_isSelectParts) {
		auto enemyCpnt = _battleComponent->GetEnemy(m_commandInfo.targetIndex)->getComponent<EnemyComponent>();

		// �F�ύX
		auto spriteCpnt = enemyCpnt->GetPartsCpntList().at(m_commandInfo.partsIndex)->gActor()->getComponent<SpriteComponent>();
		spriteCpnt->Color() = ofColor::white;

		if (down)
		{
			ofApp::getInstance()->mp_soundManager->play(3);

			if (++m_commandInfo.partsIndex >= enemyCpnt->GetPartsCpntList().size())
			{
				m_commandInfo.partsIndex = 0;
			}
			string targetInfo = u8"�^�[�Q�b�g(����):" + enemyCpnt->GetPartsCpntList().at(m_commandInfo.partsIndex)->gActor()->Name();
			_battleComponent->SetMessage(move(targetInfo));
		}
		else if (up)
		{
			ofApp::getInstance()->mp_soundManager->play(3);

			if (--m_commandInfo.partsIndex < 0)
			{
				m_commandInfo.partsIndex = enemyCpnt->GetPartsCpntList().size() - 1;
			}
			string targetInfo = u8"�^�[�Q�b�g(����):" + enemyCpnt->GetPartsCpntList().at(m_commandInfo.partsIndex)->gActor()->Name();
			_battleComponent->SetMessage(move(targetInfo));
		}

		// �F�ύX
		spriteCpnt = enemyCpnt->GetPartsCpntList().at(m_commandInfo.partsIndex)->gActor()->getComponent<SpriteComponent>();
		spriteCpnt->Color() = ofColor::red;

		// ����
		if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
			// �F�ύX
			spriteCpnt->Color() = ofColor::white;
			ofApp::getInstance()->mp_soundManager->play(4);

			m_isSelectParts = true;
		}
		else {
			return nullptr;
		}
	}

	// ����
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start"))
	{
		ofApp::getInstance()->mp_soundManager->play(4);

		auto state = new AttackState();
		auto target = _battleComponent->GetEnemy(m_commandInfo.targetIndex)->getComponent<EnemyComponent>()->GetPartsCpntList().at(m_commandInfo.partsIndex)->gActor();
		auto targetPos = target->mp_parent->Pos() + target->Pos();;
		auto attack = ofApp::getInstance()->mp_prm->getPlayerParam("ATTACK");
		state->initialize(_battleComponent->GetPlayer()->Pos(), targetPos, ofApp::getInstance()->mp_prm->GetSkillList().at(m_commandInfo.bulletTypeIndex), attack, true);
		return state;
	}

	return nullptr;
}

void SelectCommandState::exit(BattleComponent * _battleComponent)
{
}

void JudgeState::enter(BattleComponent * _battleComponent)
{
	// �v���C���[�̗̑�
	const int pHP = ofApp::getInstance()->mp_prm->getPlayerParam("HP");

	// �c��̓G��
	const int eCount = _battleComponent->GetEnemyCount();

	// �v���C���[�̗̑͂��Ȃ��Ȃ���
	if (pHP <= 0)
	{
		_battleComponent->AddMessage(string(u8"�s�k"));
		result = Result::LOSE;
	}
	// �G�����ׂē|����
	else if (eCount <= 0)
	{
		_battleComponent->AddMessage(string(u8"����"));
		result = Result::WIN;
	}
	// �퓬���s
	else
	{
		result = Result::NONE;
	}
}

BattleState * JudgeState::update(BattleComponent * _battleComponent)
{
	switch (result)
	{
	case Result::NONE:
		return new TurnState();
		break;
	default:
		break;
	}

	return nullptr;
}

void JudgeState::exit(BattleComponent * _battleComponent)
{
}

void GuardJudgeState::enter(BattleComponent * _battleComponent)
{
}

BattleState * GuardJudgeState::update(BattleComponent * _battleComponent)
{
	// �e���S�ď�������J��
	if (_battleComponent->GetBulletCount() == 0)
	{
		return new JudgeState();
	}

	return nullptr;
}

void GuardJudgeState::exit(BattleComponent * _battleComponent)
{
}

void TurnState::enter(BattleComponent * _battleComponent)
{
	_battleComponent->InitAttackOrder();
	// ���s������A�N�^�[���擾
	m_turnChara = _battleComponent->GetNextAttackChara();
	_battleComponent->AddMessage(m_turnChara->Name() + u8"�̃^�[��");
}

BattleState * TurnState::update(BattleComponent * _battleComponent)
{
	// �v���C���[���G���m�F
	if (m_turnChara->getComponent<PlayerComponent>())
	{
		return new SelectCommandState();
	}
	else if(m_turnChara->getComponent<EnemyComponent>())
	{
		auto state = new AttackState();

		auto enemyCpnt = m_turnChara->getComponent<EnemyComponent>();
		state->initialize(m_turnChara->Pos(), _battleComponent->GetPlayer()->Pos(), enemyCpnt->SelectSkill(), enemyCpnt->getEnemy().Attack,false);
		
		return state;
	}

	return nullptr;
}

void TurnState::exit(BattleComponent * _battleComponent)
{
}

void AttackState::enter(BattleComponent * _battleComponent)
{
	// �e�A�N�^�[
	GameActor* actor = nullptr;
	// �v���C���[�̍U���̏ꍇ
	if (m_isPlayer)
	{
		for (int i = 0; i < m_skill.bulletCount ; ++i) {
			actor = BulletActor::createPlayerBullet(_battleComponent->gActor(), m_fromPos, m_targetPos, m_skill.attackpower , m_attack, m_skill.type);
			_battleComponent->AddBullet(actor);
		}
	}
	// �G�̍U���̏ꍇ
	else
	{
		for (int i = 0; i < m_skill.bulletCount; ++i) {
			actor = BulletActor::createEnemyBullet(_battleComponent->gActor(), m_fromPos, m_targetPos, m_skill.attackpower, m_attack, m_skill.type);
			_battleComponent->AddBullet(actor);
		}
	}
}

BattleState * AttackState::update(BattleComponent * _battleComponent)
{
	return new GuardJudgeState();
}

void AttackState::exit(BattleComponent * _battleComponent)
{
}

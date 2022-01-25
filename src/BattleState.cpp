#include "BattleState.h"
#include "stdComponent.h"
#include "EnemyType.h"
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
	_battleComponent->AddMessage("Select:" + to_string(m_commandInfo.commandTypeIndex) + "\n");
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
			if (++m_commandInfo.commandTypeIndex >= static_cast<int>(CommandType::TYPE_NUM))
			{
				m_commandInfo.commandTypeIndex = 0;
			}
			string info = "Select:" + to_string(m_commandInfo.commandTypeIndex) + "\n";
			_battleComponent->SetMessage(info);
		}
		else if (up)
		{
			if (--m_commandInfo.commandTypeIndex < 0)
			{
				m_commandInfo.commandTypeIndex = static_cast<int>(CommandType::TYPE_NUM) - 1;
			}
			string info = "Select:" + to_string(m_commandInfo.commandTypeIndex) + "\n";
			_battleComponent->SetMessage(info);
		}

		// ����
		if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
			m_isSelectCommandType = true;

			auto commandType = static_cast<CommandType>(m_commandInfo.commandTypeIndex);
			switch (commandType)
			{
			case BattleState::CommandType::SKILL:
				_battleComponent->SetMessage("Select Skill:" + BulletComponent::getBullet(static_cast<BulletType>(m_commandInfo.bulletTypeIndex)).bulletName);
				break;
			case BattleState::CommandType::ITEM:
			{
				auto itemCpnt = _battleComponent->gActor()->getComponent<ItemComponent>();
				_battleComponent->SetMessage("Select Item:" + itemCpnt->getItemName(0) + "\n");
				break;
			}
			default:
				break;
			}

			return nullptr;
		}
		else {
			return nullptr;
		}
	}

	if (!m_isSelectBulletType) {
		auto commandType = static_cast<CommandType>(m_commandInfo.commandTypeIndex);
		switch (commandType)
		{
		case BattleState::CommandType::SKILL:	// �X�L���I��
		{
			if (down)
			{
				if (++m_commandInfo.bulletTypeIndex >= static_cast<int>(BulletType::TypeNum))
				{
					m_commandInfo.bulletTypeIndex = 0;
				}
				string bulletInfo = "Select Skill:";
				bulletInfo.append(BulletComponent::getBullet(static_cast<BulletType>(m_commandInfo.bulletTypeIndex)).bulletName.c_str());
				_battleComponent->SetMessage(bulletInfo);
			}
			else if (up)
			{
				if (--m_commandInfo.bulletTypeIndex < 0)
				{
					m_commandInfo.bulletTypeIndex = static_cast<int>(BulletType::TypeNum) - 1;
				}
				string bulletInfo = "Select Skill:";
				bulletInfo.append(BulletComponent::getBullet(static_cast<BulletType>(m_commandInfo.bulletTypeIndex)).bulletName.c_str());
				_battleComponent->SetMessage(bulletInfo);
			}

			// ����
			if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
				m_isSelectBulletType = true;
				string targetInfo = "Select Target:" + _battleComponent->GetEnemy(m_commandInfo.targetIndex)->Name() + "\n";
				_battleComponent->SetMessage(targetInfo);

				return nullptr;
			}
			else {
				return nullptr;
			}

			break;
		}
		case BattleState::CommandType::ITEM:	// �A�C�e��
		{
			auto itemCpnt = _battleComponent->gActor()->getComponent<ItemComponent>();

			static int itemIndex = 0;
			if (down)
			{
				if (++itemIndex >= ItemType::NumItems)
				{
					itemIndex = 0;
				}
				string itemInfo = "Select Item:" + itemCpnt->getItemName(itemIndex) + "\n";
				_battleComponent->SetMessage(itemInfo);
			}
			else if (up)
			{
				if (--itemIndex < 0)
				{
					itemIndex = ItemType::NumItems - 1;
				}
				string itemInfo = "Select Item:" + itemCpnt->getItemName(itemIndex) + "\n";
				_battleComponent->SetMessage(itemInfo);
			}

			// ����
			if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
				itemCpnt->useItem(itemIndex);
				itemIndex = 0;
				_battleComponent->SetMessage(itemCpnt->getItem(itemIndex).m_iParam.itemName + u8"���g�p����\n");
				return new JudgeState();
			}
			else {
				return nullptr;
			}

			break;
		}
		default:
			break;
		}
	}

	// �G�I��
	if (!m_isSelectTarget) {
		auto enemyCpnt = _battleComponent->GetEnemy(m_commandInfo.targetIndex)->getComponent<EnemyComponent>();
		// �F�ύX
		enemyCpnt->SetColor(ofColor::white);

		if (down)
		{
			if (++m_commandInfo.targetIndex >= _battleComponent->GetEnemyCount())
			{
				m_commandInfo.targetIndex = 0;
			}

			string targetInfo = "Select Target:" + _battleComponent->GetEnemy(m_commandInfo.targetIndex)->Name() + "\n";
			_battleComponent->SetMessage(targetInfo);
		}
		else if (up)
		{
			if (--m_commandInfo.targetIndex < 0)
			{
				m_commandInfo.targetIndex = _battleComponent->GetEnemyCount() - 1;
			}

			string targetInfo = "Select Target:" + _battleComponent->GetEnemy(m_commandInfo.targetIndex)->Name() + "\n";
			_battleComponent->SetMessage(targetInfo);
		}

		enemyCpnt = _battleComponent->GetEnemy(m_commandInfo.targetIndex)->getComponent<EnemyComponent>();
		// �F�ύX
		enemyCpnt->SetColor(ofColor::red);

		// ����
		if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")){
			m_isSelectTarget = true;

			// �F�ύX
			enemyCpnt->SetColor(ofColor::white);

			string targetInfo = "Select Target:" + enemyCpnt->GetPartsCpntList().at(m_commandInfo.partsIndex)->gActor()->Name() + "\n";
			_battleComponent->SetMessage(targetInfo);
			return nullptr;
		}
		else {
			return nullptr;
		}
	}

	// ���ʑI��
	if (!m_isSelectParts) {
		auto enemyCpnt = _battleComponent->GetEnemy(m_commandInfo.targetIndex)->getComponent<EnemyComponent>();

		// �F�ύX
		auto spriteCpnt = enemyCpnt->GetPartsCpntList().at(m_commandInfo.partsIndex)->gActor()->getComponent<SpriteComponent>();
		spriteCpnt->Color() = ofColor::white;

		if (down)
		{
			if (++m_commandInfo.partsIndex >= enemyCpnt->GetPartsCpntList().size())
			{
				m_commandInfo.partsIndex = 0;
			}
			string targetInfo = "Select Target:" + enemyCpnt->GetPartsCpntList().at(m_commandInfo.partsIndex)->gActor()->Name() + "\n";
			_battleComponent->SetMessage(targetInfo);
		}
		else if (up)
		{
			if (--m_commandInfo.partsIndex < 0)
			{
				m_commandInfo.partsIndex = enemyCpnt->GetPartsCpntList().size() - 1;
			}
			string targetInfo = "Select Target:" + enemyCpnt->GetPartsCpntList().at(m_commandInfo.partsIndex)->gActor()->Name() + "\n";
			_battleComponent->SetMessage(targetInfo);
		}

		// �F�ύX
		spriteCpnt = enemyCpnt->GetPartsCpntList().at(m_commandInfo.partsIndex)->gActor()->getComponent<SpriteComponent>();
		spriteCpnt->Color() = ofColor::red;

		// ����
		if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
			// �F�ύX
			spriteCpnt->Color() = ofColor::white;

			m_isSelectParts = true;
		}
		else {
			return nullptr;
		}
	}

	// ����
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start"))
	{
		auto state = new AttackState();
		auto target = _battleComponent->GetEnemy(m_commandInfo.targetIndex)->getComponent<EnemyComponent>()->GetPartsCpntList().at(m_commandInfo.partsIndex)->gActor();
		auto targetPos = target->mp_parent->Pos() + target->Pos();;
		auto attack = ofApp::getInstance()->mp_prm->getPlayerParam("ATTACK");
		state->initialize(_battleComponent->GetPlayer()->Pos(), targetPos, static_cast<BulletType>(m_commandInfo.bulletTypeIndex), 1, attack, true);
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
		_battleComponent->AddMessage(string(u8"�s�k\n"));
		result = Result::LOSE;
	}
	// �G�����ׂē|����
	else if (eCount <= 0)
	{
		_battleComponent->AddMessage(string(u8"����\n"));
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
	_battleComponent->AddMessage(m_turnChara->Name() + u8"�̃^�[��\n");
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
		 auto skill = enemyCpnt->SelectSkill();
		state->initialize(m_turnChara->Pos(), _battleComponent->GetPlayer()->Pos(), skill.type,skill.bulletCount, enemyCpnt->getEnemy().Attack,false);
		
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
		for (int i = 0; i < m_bulletCount; ++i) {
			actor = BulletActor::createPlayerBullet(_battleComponent->gActor(), m_fromPos, m_targetPos, m_attack,m_bulletType);
			_battleComponent->AddBullet(actor);
		}
	}
	// �G�̍U���̏ꍇ
	else
	{
		for (int i = 0; i < m_bulletCount; ++i) {
			actor = BulletActor::createEnemyBullet(_battleComponent->gActor(), m_fromPos, m_targetPos, m_attack, m_bulletType);
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

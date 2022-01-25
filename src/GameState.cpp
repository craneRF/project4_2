#include "ofApp.h"
#include "GameState.h"
#include "GameActor.h"
#include "EnemyType.h"
#include "ItemType.h"
#include "stdComponent.h"
#include "BattleHUD.h"
#include "LoadCSVFile.h"
#include "MapState.h"
#include "BattleState.h"
#include "CreateActor.h"

/*
* 1.hierarchyRoot_��GameMainCtrlComponent���ŃV�[����������A�A�N�^�[�̐������s�����Ƃ���A
*   GameMainCtrlComponent�͏��Active��Ԃł���Aupdate()���s��Ȃ���΂Ȃ�Ȃ��B(hierarchyRoot_���̂�Active��ԂłȂ��Ă��ǂ�)
* 2.GameMainCtrlComponent��update()���ɑ��݂���GameState����ɍs���邽�߁AGameState��update()����ɍs����B
* 3.GameState��update()���ōs����uGameActor�v�E�uUIActor�v�E�uCoponent�����C���X�^���X�v�̃v���p�e�B(Actor�ł���m_pos��m_rotAngle�APos()�Ȃ�)
*   �ɑ΂��鏈���͂��ꂼ�ꂪ�ǂ�ȏ�Ԃ��낤���ⓚ���p�ōs����B
*
* �ȏ��3�_��GameActor�EUIActor�EComponent ���ꂼ���State�����̓s����A
* GameState��update()���ł�
* �uGameActor�v�E�uUIActor�v�E�uCoponent�����C���X�^���X�v�̃v���p�e�B(Actor�ł���m_pos��m_rotAngle�APos()�Ȃ�)��ς��Ȃ��ł��������B
* �����ύX���K�v�ɂȂ����Ȃ�A���ړI�ɕς���̂ł͂Ȃ��A���ꂼ��̃v���p�e�B�ɉe���̂Ȃ��ϐ�������āA��������ԐړI�Ƀv���p�e�B��ω�������悤�ɂ��Ă��������B
* �ԐړI�ɕύX����͖̂ʓ|���������A��₱�����Ȃ�̂Ŕ񐄏��B

* ��F
	�EGameActor�̃v���p�e�B�̏ꍇ�A�����p��Component�����A����Component��update()���ŕύX����B
	�EUIActor�̃v���p�e�B�̏ꍇ�A���ꂪ���݂��Ă���UIScreen��update()���ŕύX����B
	�EComponent�����C���X�^���X�̃v���p�e�B�̏ꍇ�A����update()���ŕύX���邩
	 �������͂���Component������GameActor��update()�ŕύX����B

	���ŏI�I�ɉ��������������Ƃ����ƁA
	GameState��update()���͋ɗ̓V�[������݂̂ɂ��A
	��ɏ�����Ă���悤�Ȑ݌v�ɂ��Ă��������A�Ƃ������Ƃł��B
*/

void GameStateTitle::enter()
{
	ofApp::getInstance()->hierarchyRoot_->m_fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);

	mp_fontActor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	mp_fontActor->Pos() = { (float)Define::FULLWIN_W / 5, (float)Define::FULLWIN_H / 5 };
	mp_fontActor->addComponent<FontRendererComponent>()->
		initialize(u8"�^�C�g���V�[��", 18);

	// �^�C�g���Ȃ̂ŁA�v���C���[�̃p�����[�^��������
	ofApp::getInstance()->mp_prm->initialize();

	// �}�b�v�̃N���A
	MapComponent::ClearMap();

	ofApp::getInstance()->mp_soundManager->setVolume(0, 0.4f);
	ofApp::getInstance()->mp_soundManager->setVolume(1, 0.4f);
	ofApp::getInstance()->mp_soundManager->loop(0);

	// FPS�\��
	//mp_actor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	//mp_actor->Pos() = { 500,100 };
	//mp_actor->addComponent<FontRendererComponent>()->
	//	initialize(ofToString(ofGetFrameRate()), 18, { 0,0,0 }, ofColor::white, {3, 3, 3}, "keifont.ttf");

	mp_actor1 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	//�^�C�g���w�i
	{
		auto spriteCpnt_bg = mp_actor1->addComponent<SpriteComponent>();
		spriteCpnt_bg->initialize("backGround_title_1.jpg");
	}

	//�^�C�g�����S
	{
		auto spriteCpnt_title = mp_actor1->addComponent<SpriteComponent>();
		spriteCpnt_title->initialize("title.png");
		spriteCpnt_title->AlignPivotCenter();
		spriteCpnt_title->Offset() += {(float)Define::FULLWIN_W / 2, (float)Define::FULLWIN_H / 2 - 200.f};
	}

	mp_actor1->addComponent<FontRendererComponent>()->
		initialize(ofToString(ofApp::getInstance()->mp_prm->getPlayerParam("HP")), 18, { 300,400 });

	mp_itemlist = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	mp_itemlist->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->mp_itemManager->DisplayItemList(), 18, { 400,600 });

	// ������@��\������A�N�^�[
	{
		mp_operationFontactor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_operationFontactor->Pos() = { 0.f, (float)Define::FULLWIN_H * 0.9f };
		mp_operationFontactor->addComponent<FontRendererComponent>()->initialize(u8"Space�L�[:�X�^�[�g");
	}

	//PlayerActor::createPlayer(ofApp::getInstance()->hierarchyRoot_.get(), { 400,50 });
	//EnemyActor::createEnemy(ofApp::getInstance()->hierarchyRoot_.get(), { 200,50 },NONE);
//	mp_marin = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>("Arrow");
//	mp_marin->Pos() = { 750, 400 };
//	mp_marin->Scale() = { 1.0f, 1.0f };
//mp_marin->drawfuncVec.emplace_back([]() { ofSetColor(ofColor::red); });
//	mp_marin->addComponent<SpriteComponent>()->
//		initialize("Arrow.png", { 0,0 }, {1, 1}, 0.0f);
//	mp_marin->addComponent<SpriteComponent>()->
//		initialize("Arrow.png", { -200,0 }, { 0.75f, 0.75f }, 0.0f);
//	mp_marin->addComponent<SpriteComponent>()->
//		initialize("Arrow.png", { 200,0 }, { 0.25f, 0.25f }, 0.0f);
//	mp_marin->addComponent<SpriteComponent>()->
//		initialize("Arrow.png", { 0,200 }, { 1.25f, 0.75f }, 0.0f);
//	
//
//	mp_rect = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
//	mp_rect->initialize({ 50.0f, 50.0f }, "abc");
//	mp_rect->addComponent<SpriteComponent>()->initialize("NoSearch.png");
//	auto spriteSize = mp_rect->getComponent<SpriteComponent>()->ImageSize();
//	mp_rect->addComponent<BoxComponent>()->initialize({ 0.f, 0.f, 0.f }, spriteSize.x, spriteSize.y, CollisionType::DEFAULT);
//	//mp_rect->drawfuncVec.emplace_back([this]() {ofDrawRectangle(mp_rect->WorldPos(), 50.0f, 50.0f); });
//
//	mp_rect2 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
//	mp_rect2->initialize({ 150.0f, 50.0f }, "def");
//	mp_rect2->addComponent<SpriteComponent>()->initialize("NoSearch.png");
//	auto spriteSize2 = mp_rect2->getComponent<SpriteComponent>()->ImageSize();
//	mp_rect2->addComponent<BoxComponent>()->initialize({ 0.f, 0.f, 0.f }, spriteSize2.x, spriteSize2.y, CollisionType::DEFAULT);
//	//mp_rect2->drawfuncVec.emplace_back([this]() {ofDrawRectangle(mp_rect2->WorldPos(), 50.0f, 50.0f); });
//
//	mp_rect->getComponent<BoxComponent>()->m_onCollisionFunc = [this](CollisionComponent* _other) 
//	{
//		_other->gActor()->Pos() += { 0.0f, 0.5f };
//	};
//
//	mp_rect->addComponent<MoveComponent>()->AddMovePos({ 4.0f, 0.0f });
//
//	mp_BHUD = ofApp::getInstance()->addUICanvas<BattleHUD>();
}

GameState* GameStateTitle::update()
{
	//mp_actor->getComponent<FontRendererComponent>()->String() = ofToString(ofGetLastFrameTime()/*ofGetElapsedTimeMillis()*/);

	mp_actor1->getComponent<FontRendererComponent>()->String() = ofToString(ofApp::getInstance()->mp_prm->getPlayerParam("HP"));
	mp_itemlist->getComponent<FontRendererComponent>()->String() = ofApp::getInstance()->mp_itemManager->DisplayItemList();
	auto itemCmp = mp_actor1->addComponent<ItemComponent>();
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Fire")) {
		/*ofApp::getInstance()->mp_prm->setPlayerParam("HP", 50);*/
		itemCmp->useItem(ItemType::ATKUp);
	}
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Bomb")) {
		/*m_prmInState->setPlayerParam("HP", 100);*/
		itemCmp->useItem(ItemType::POTION);
	}
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
		return &GameMainCtrlComponent::m_gameStateMap;
		//return &GameMainCtrlComponent::m_gameStateBattle;
	}
	/*if (ofApp::getInstance()->mp_inputManager->getButtonUp("HUD")) {
		if (mp_BHUD->GetActorState() == BattleHUD::ActorState::EPause || mp_BHUD->GetActorDrawState() == BattleHUD::ActorDrawState::EHidden) {
			mp_BHUD->StateActive();
			mp_BHUD->StateVisible();
		}
		else if (mp_BHUD->GetActorState() == BattleHUD::ActorState::EActive || mp_BHUD->GetActorDrawState() == BattleHUD::ActorDrawState::EVisible) {
			mp_BHUD->StatePause();
			mp_BHUD->StateHidden();
		}
	}*/
	//mp_rect->getComponent<MoveComponent>()->AddMovePos({ 20.0f, 0.0f });

	return nullptr;
}

void GameStateTitle::exit()
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild<GameActor>();
	ofApp::getInstance()->mp_soundManager->stop(0);
	ofApp::getInstance()->mp_soundManager->play(4);
}

void GameStateClear::enter()
{
	ofApp::getInstance()->mp_soundManager->setVolume(0, 0.4f);
	ofApp::getInstance()->mp_soundManager->loop(0);

	mp_actor1 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	//�w�i
	{
		auto spriteCpnt_bg = mp_actor1->addComponent<SpriteComponent>();
		spriteCpnt_bg->initialize("backGround_gaemclear_1.jpg");
	}

	// ������@��\������A�N�^�[
	{
		mp_operationFontactor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_operationFontactor->Pos() = { 0.f, (float)Define::FULLWIN_H * 0.9f };
		mp_operationFontactor->addComponent<FontRendererComponent>()->initialize(u8"Space�L�[:�^�C�g���ɖ߂�");
	}
}

GameState * GameStateClear::update()
{
	// �^�C�g���V�[���֑J��
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
		return &GameMainCtrlComponent::m_gameStateTitle;
	}

	return nullptr;
}

void GameStateClear::exit()
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild<GameActor>();
	ofApp::getInstance()->mp_soundManager->stop(0);
	ofApp::getInstance()->mp_soundManager->play(4);
}

void GameStateOver::enter()
{
	ofApp::getInstance()->mp_soundManager->setVolume(0, 0.4f);
	ofApp::getInstance()->mp_soundManager->loop(0);

	mp_actor1 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	//�w�i
	{
		auto spriteCpnt_bg = mp_actor1->addComponent<SpriteComponent>();
		spriteCpnt_bg->initialize("backGround_gaemover_1.jpg");
	}

	// �I������\������A�N�^�[
	{
		// �I�����J�E���g
		int count = 0;
		mp_actor2 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_actor2->Pos() = { (float)Define::FULLWIN_W * 0.5f, (float)Define::FULLWIN_H * 0.8f };
		{
			// �I�����P
			if (ofApp::getInstance()->mp_prm->getPlayerParam("LIFE") != 0) {
				// �t�H���g
				auto fontCpnt = mp_actor2->addComponent<FontRendererComponent>();
				fontCpnt->initialize(u8"��������", 18, { 0,0,0 }, ofColor::gray);
				m_selectFontCpntList.emplace_back(fontCpnt);

				m_funcList.emplace_back([] {
					// �c�@�����炷
					ofApp::getInstance()->mp_prm->setPlayerParam("LIFE", ofApp::getInstance()->mp_prm->getPlayerParam("LIFE") - 1);
					// �}�b�v��
					MapComponent::BackStep();
					return &GameMainCtrlComponent::m_gameStateMap;
					}
				);

				++count;
			}
			// �I�����Q
			{
				// �t�H���g
				auto fontCpnt = mp_actor2->addComponent<FontRendererComponent>();
				fontCpnt->initialize(u8"�^�C�g���ɖ߂�", 18, { 0,36.f * count,0 }, ofColor::gray);
				m_selectFontCpntList.emplace_back(fontCpnt);

				m_funcList.emplace_back([] {
					MapComponent::ClearMap();
					return &GameMainCtrlComponent::m_gameStateTitle;
					}
				);
			}
		}
	}

	// ������@��\������A�N�^�[
	{
		mp_operationFontactor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_operationFontactor->Pos() = { 0.f, (float)Define::FULLWIN_H * 0.9f };
		if (ofApp::getInstance()->mp_prm->getPlayerParam("LIFE") != 0) {
			mp_operationFontactor->addComponent<FontRendererComponent>()->initialize(u8"Space�L�[:����\nWS�L�[:�I��");
		}
		else {
			mp_operationFontactor->addComponent<FontRendererComponent>()->initialize(u8"Space�L�[:����");
		}
	}
}

GameState * GameStateOver::update()
{
	m_selectFontCpntList.at(m_selectIndex)->Color() = ofColor::gray;

	// �I��
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Up"))
	{
		ofApp::getInstance()->mp_soundManager->play(3);

		if (--m_selectIndex < 0)
		{
			m_selectIndex = m_selectFontCpntList.size() - 1;
		}
	}
	else if (ofApp::getInstance()->mp_inputManager->getButtonDown("Down"))
	{
		ofApp::getInstance()->mp_soundManager->play(3);

		if (++m_selectIndex >= m_selectFontCpntList.size())
		{
			m_selectIndex = 0;
		}
	}

	m_selectFontCpntList.at(m_selectIndex)->Color() = ofColor::white;

	// ����
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
		return m_funcList.at(m_selectIndex)();
	}

	return nullptr;
}


void GameStateOver::exit()
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild<GameActor>();
	ofApp::getInstance()->mp_soundManager->stop(0);
	ofApp::getInstance()->mp_soundManager->play(4);

	m_selectIndex = 0;
	m_funcList.clear();
	m_selectFontCpntList.clear();
}

void GameStateMap::enter()
{
	ofApp::getInstance()->mp_soundManager->loop(1);

	/*for (int i = 0; i < 900; i++) {
		auto actor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		actor->Pos() = { float(i), float(i) };
		actor->addComponent<SpriteComponent>();
	}*/

	auto mapActor = GameActor::createMap(ofApp::getInstance()->hierarchyRoot_.get(), { 0.f, 0.f, 0.f });
	mp_mapComp = mapActor->getComponent<MapComponent>();
	mp_mapComp->Initialize();

	auto spriteCpnt_bg = mapActor->addComponent<SpriteComponent>();
	spriteCpnt_bg->initialize("backGround_map_2.jpg");

	mp_fontActor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	mp_fontActor->Pos() = { 0, 20 };
	mp_fontActor->addComponent<FontRendererComponent>()->
		initialize(u8"�}�b�v�V�[��");

	// ������@��\������A�N�^�[
	{
		mp_operationFontactor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_operationFontactor->Pos() = { 0.f, (float)Define::FULLWIN_H * 0.9f };
		mp_operationFontactor->addComponent<FontRendererComponent>()->initialize(u8"Space�L�[:����\nWS�L�[:�}�X�I��");
	}
}
GameState * GameStateMap::update()
{
	auto kind = mp_mapComp->GetResKind();
	switch (kind)
	{
	case StepKind::EVENT:
		return &GameMainCtrlComponent::m_gameStateEvent;
		break;
	case StepKind::BATTLE:
		return &GameMainCtrlComponent::m_gameStateBattle;
	case StepKind::GOAL:
		GameMainCtrlComponent::m_gameStateBattle.SetIsBossBattle(true);
		return &GameMainCtrlComponent::m_gameStateBattle;
		//return &GameMainCtrlComponent::m_gameStateClear;
		break;
	default:
		break;
	}
	return nullptr;
}

void GameStateMap::exit()
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild<GameActor>();
	ofApp::getInstance()->mp_soundManager->stop(1);
}


void GameStateBattle::enter()
{
	// �퓬�V�X�e��������
	{
		// �퓬�R���|�[�l���g
		mp_BattleComp = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>()->addComponent<BattleComponent>();
		mp_BattleComp->Initialize(m_isBossBattle);
	}

	// �u�퓬�V�[���v�ƕ\������A�N�^�[
	{
		mp_fontActor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_fontActor->Pos() = { 0, 20 };
		mp_fontActor->addComponent<FontRendererComponent>()->
			initialize(u8"�퓬�V�[��");
	}

	// �v���C���[��HP��\������A�N�^�[
	{
		mp_hpFontActor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_hpFontActor->Pos() = { (float)Define::FULLWIN_W * 0.3f, (float)Define::FULLWIN_H * 0.9f };
		mp_hpFontActor->addComponent<FontRendererComponent>()->
			initialize(u8"");
	}

	// �퓬�̃��b�Z�[�W��\������A�N�^�[
	{
		mp_actor2 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_actor2->Pos() = { (float)Define::FULLWIN_W * 0.7f, (float)Define::FULLWIN_H * 0.8f };

		// �t���[��
		auto spriteCpnt = mp_actor2->addComponent<SpriteComponent>();
		spriteCpnt->initialize("button1.png", { 0,0,0 }, { 0.8f,0.5f });
		spriteCpnt->AlignPivotCenter();
		spriteCpnt->Offset().x *= 0.2f;
		// ���b�Z�[�W
		mp_actor2->addComponent<FontRendererComponent>()->
			initialize(ofToString(""));
	}

	// ������@��\������A�N�^�[
	{
		mp_operationFontactor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_operationFontactor->Pos() = { 0.f, (float)Define::FULLWIN_H * 0.9f };
		mp_operationFontactor->addComponent<FontRendererComponent>()->initialize(u8"Space�L�[:�U��\nWS�L�[:�e�؂�ւ�");
	}

	mp_prePrameter = make_unique<Parameter>(*ofApp::getInstance()->mp_prm);
}

GameState * GameStateBattle::update()
{
	// ���b�Z�[�W�\��
	mp_actor2->getComponent<FontRendererComponent>()->String() = mp_BattleComp->GetInfo();

	// HP�\��
	int playerHP = ofApp::getInstance()->mp_prm->getPlayerParam("HP");
	mp_hpFontActor->getComponent<FontRendererComponent>()->String() = u8"�v���C���[��HP:" + to_string(playerHP);

	// ���s�̌���
	auto result = mp_BattleComp->GetResult();
	switch (result)
	{
	case Result::WIN:
		if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")){
			if (m_isBossBattle) {
				// �N���A�V�[����
				return &GameMainCtrlComponent::m_gameStateClear;
			}
			else {
				// �}�b�v�V�[����
				return &GameMainCtrlComponent::m_gameStateMap;
			}
		}
	case Result::LOSE:
		if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
			ofApp::getInstance()->mp_prm.swap(mp_prePrameter);
			return &GameMainCtrlComponent::m_gameStateOver;
		}
	default:
		break;
	}

	return nullptr;
}

void GameStateBattle::exit()
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild<GameActor>();
	ofApp::getInstance()->mp_soundManager->stop(2);
	m_isBossBattle = false;
}

void GameStateEvent::enter()
{
	mp_actor1 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	//�w�i
	{
		auto spriteCpnt_bg = mp_actor1->addComponent<SpriteComponent>();
		spriteCpnt_bg->initialize("backGround_title_1.jpg");
	}

	m_isDead = false;

	mp_prePrameter = make_unique<Parameter>(*ofApp::getInstance()->mp_prm);

	auto eventIndex = static_cast<EVENT_INDEX>(rand() % static_cast<int>(EVENT_INDEX::INDEX_NUM));
	string eventStrInfo = "";
	switch (eventIndex)
	{
	case GameStateEvent::EVENT_INDEX::NONE:
		eventStrInfo = u8"�����N����Ȃ������B\n";
		break;
	case GameStateEvent::EVENT_INDEX::HEAL:
	{
		Effect::healHP(1);
		int hp = ofApp::getInstance()->mp_prm->getPlayerParam("HP");
		eventStrInfo = u8"�̗͂�1�񕜂����B\n���݂�HP:" + to_string(hp) + "\n";
		break;
	}
	case GameStateEvent::EVENT_INDEX::DAMAGE:
	{
		Effect::healHP(-1);
		int hp = ofApp::getInstance()->mp_prm->getPlayerParam("HP");
		eventStrInfo = u8"1�_���[�W���󂯂�\n";
		// �_���[�W���󂯂���������Ă��邩
		if (hp <= 0)
		{
			eventStrInfo += u8"HP��0�ɂȂ����B\n";
			m_isDead = true;
			ofApp::getInstance()->mp_prm.swap(mp_prePrameter);
		}
		else
		{
			eventStrInfo += u8"���݂�HP:" + to_string(hp) + "\n";
		}
		break;
	}
	case GameStateEvent::EVENT_INDEX::ATTACK_UP:
	{
		Effect::increaseATK(1);
		int attack = ofApp::getInstance()->mp_prm->getPlayerParam("ATTACK");
		eventStrInfo = u8"�U���͂�1�オ�����B\n���݂̍U����:" + to_string(attack) + "\n";
		break;
	}
	case GameStateEvent::EVENT_INDEX::INDEX_NUM:
		break;
	default:
		break;
	}

	// ���b�Z�[�W��\������A�N�^�[
	{
		mp_actor2 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_actor2->Pos() = { (float)Define::FULLWIN_W * 0.7f, (float)Define::FULLWIN_H * 0.8f };

		// �t���[��
		auto spriteCpnt = mp_actor2->addComponent<SpriteComponent>();
		spriteCpnt->initialize("button1.png", { 0,0,0 }, { 0.8f,0.5f });
		spriteCpnt->AlignPivotCenter();
		spriteCpnt->Offset().x *= 0.2f;
		// ���b�Z�[�W
		mp_actor2->addComponent<FontRendererComponent>()->
			initialize(u8"�C�x���g�V�[��\n" + eventStrInfo);
	}

	// ������@��\������A�N�^�[
	{
		mp_operationFontactor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_operationFontactor->Pos() = { 0.f, (float)Define::FULLWIN_H * 0.9f };
		if (m_isDead)
		{
			mp_operationFontactor->addComponent<FontRendererComponent>()->initialize(u8"Space�L�[:�Q�[���I�[�o�[�V�[���ֈړ�");
		}
		else
		{
			mp_operationFontactor->addComponent<FontRendererComponent>()->initialize(u8"Space�L�[:�}�b�v�V�[���ֈړ�");
		}
	}
}

GameState * GameStateEvent::update()
{
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start"))
	{
		if (m_isDead)
		{
			return &GameMainCtrlComponent::m_gameStateOver;
		}
		else
		{
			return &GameMainCtrlComponent::m_gameStateMap;
		}
	}

	return nullptr;
}

void GameStateEvent::exit()
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild<GameActor>();
	//ofApp::getInstance()->mp_soundManager->stop(1);
}

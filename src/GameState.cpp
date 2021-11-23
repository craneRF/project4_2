#include "ofApp.h"
#include "GameState.h"
#include "GameActor.h"
#include "EnemyType.h"
#include "stdComponent.h"
#include "BattleHUD.h"
#include "LoadCSVFile.h"

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

void GameStateTitle::enter(Parameter _pprm)
{
	mp_fontActor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	mp_fontActor->Pos() = { (float)Define::WIN_W / 2, (float)Define::WIN_H / 2 };
	mp_fontActor->addComponent<FontRendererComponent>()->
		initialize(u8"�^�C�g���V�[��", 18);
	*m_prmInState = _pprm;

	//ofApp::getInstance()->mp_soundManager->setVolume(0, 0.4f);
	//ofApp::getInstance()->mp_soundManager->setVolume(1, 0.4f);
	//ofApp::getInstance()->mp_soundManager->loop(0);
	mp_actor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	mp_actor->Pos() = { 500,100 };
	mp_actor->addComponent<FontRendererComponent>()->
		initialize(ofToString(ofGetFrameRate()), 18, { 0,0,0 }, ofColor::white, {3, 3, 3}, "keifont.ttf");
	//"keifont.ttf"

	mp_actor1 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	mp_actor1->Pos() = { 500,300 };
	mp_actor1->addComponent<FontRendererComponent>()->
		initialize(ofToString(m_prmInState->getPlayerParam("HP")), 18);

	//PlayerActor::createPlayer(ofApp::getInstance()->hierarchyRoot_.get(), { 400,50 });
	//EnemyActor::createEnemy(ofApp::getInstance()->hierarchyRoot_.get(), { 200,50 },NONE);
	
	mp_marin = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>("Arrow");
	mp_marin->Pos() = { 750, 400 };
	mp_marin->Scale() = { 1.0f, 1.0f };
	/*mp_marin->addComponent<SpriteComponent>()->
		initialize("marine_icon.png");*/
mp_marin->drawfuncVec.emplace_back([]() { ofSetColor(ofColor::red); });
	mp_marin->addComponent<SpriteComponent>()->
		initialize("Arrow.png", { 0,0 }, {1, 1}, 0.0f);
	mp_marin->addComponent<SpriteComponent>()->
		initialize("Arrow.png", { -200,0 }, { 0.75f, 0.75f }, 0.0f);
	mp_marin->addComponent<SpriteComponent>()->
		initialize("Arrow.png", { 200,0 }, { 0.25f, 0.25f }, 0.0f);
	mp_marin->addComponent<SpriteComponent>()->
		initialize("Arrow.png", { 0,200 }, { 1.25f, 0.75f }, 0.0f);
	

	mp_rect = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	//mp_rect->Pos() = { 50.0f, 50.0f };
	mp_rect->initialize({ 50.0f, 50.0f }, "abc");
	mp_rect->addComponent<BoxComponent>()->initialize({ 0.f, 0.f, 0.f }, 50.0f, 50.0f, CollisionType::DEFAULT);
	mp_rect->drawfuncVec.emplace_back([this]() {ofDrawRectangle(mp_rect->WorldPos(), 50.0f, 50.0f); });
	//mp_rect->drawfuncVec.emplace_back([]() { ofSetColor(ofColor::red); });

	mp_rect2 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	//mp_rect2->Pos() = { 200.0f, 50.0f };
	mp_rect2->initialize({ 200.0f, 50.0f }, "def");
	mp_rect2->addComponent<BoxComponent>()->initialize({ 0.f, 0.f, 0.f }, 50.0f, 50.0f, CollisionType::DEFAULT);
	mp_rect2->drawfuncVec.emplace_back([this]() {ofDrawRectangle(mp_rect2->WorldPos(), 50.0f, 50.0f); });
	//mp_rect2->drawfuncVec.emplace_back([]() { ofSetColor(ofColor::red); });

	mp_rect->getComponent<BoxComponent>()->m_onCollisionFunc = [this](CollisionComponent* _other) 
	{
	    //mp_rect->Pos() += { 0.0f, 1.0f };
		_other->gActor()->Pos() += { 0.0f, 1.0f };
		//_other->gActor()->Pos() = { 200.0f, 150.0f };
		//_other->gActor()->drawfuncVec.pop_back();
		//_other->gActor()->drawfuncVec.emplace_back([this]() {ofDrawRectangle(mp_rect->Pos(), 50.0f, 50.0f); });
		//_other->gActor()->drawfuncVec.emplace_back([]() { ofSetColor(ofColor::red); });
		//mp_rect->drawfuncVec.emplace_back([]() { ofSetColor(ofColor::red); });
	};
	/*mp_rect2->getComponent<BoxComponent>()->m_onCollisionFunc = [this](CollisionComponent* _other)
	{
		_other->gActor()->Pos() += { 0.0f, 1.0f };
		_other->gActor()->drawfuncVec.pop_back();
		_other->gActor()->drawfuncVec.emplace_back([this]() {ofDrawRectangle(mp_rect->Pos(), 50.0f, 50.0f); });
		_other->gActor()->drawfuncVec.emplace_back([]() { ofSetColor(ofColor::red); });
		mp_rect->drawfuncVec.emplace_back([]() { ofSetColor(ofColor::red); });
	};*/
	mp_rect->addComponent<MoveComponent>()->AddMovePos({ 2.0f, 0.0f });

	mp_BHUD = ofApp::getInstance()->addUICanvas<BattleHUD>();

	
}

GameState* GameStateTitle::update()
{
	mp_actor->getComponent<FontRendererComponent>()->String() = ofToString(ofGetLastFrameTime()/*ofGetElapsedTimeMillis()*/);
	mp_actor1->getComponent<FontRendererComponent>()->String() = ofToString(m_prmInState->getPlayerParam("HP"));
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Fire")) {
		m_prmInState->setPlayerParam("HP", 50);
	}
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Bomb")) {
		m_prmInState->setPlayerParam("HP", 100);
	}
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
		return &GameMainCtrlComponent::m_gameStateMap;
		//return &GameMainCtrlComponent::m_gameStateBattle;
	}

	if (ofApp::getInstance()->mp_inputManager->getButtonUp("HUD")) {
		if (mp_BHUD->GetActorState() == BattleHUD::ActorState::EPause || mp_BHUD->GetActorDrawState() == BattleHUD::ActorDrawState::EHidden) {
			mp_BHUD->StateActive();
			mp_BHUD->StateVisible();
		}
		else if (mp_BHUD->GetActorState() == BattleHUD::ActorState::EActive || mp_BHUD->GetActorDrawState() == BattleHUD::ActorDrawState::EVisible) {
			mp_BHUD->StatePause();
			mp_BHUD->StateHidden();
		}
	}
	mp_rect->getComponent<MoveComponent>()->AddMovePos({ 20.0f, 0.0f });

	return nullptr;
}

void GameStateTitle::exit(Parameter& _pprm)
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild<GameActor>();
	ofApp::getInstance()->mp_soundManager->stop(0);
	_pprm = *m_prmInState;
}

void GameStateMap::enter(Parameter _pprm)
{
	mp_fontActor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	mp_fontActor->Pos() = { (float)Define::WIN_W / 2, (float)Define::WIN_H / 2 };
	mp_fontActor->addComponent<FontRendererComponent>()->
		initialize(u8"�}�b�v�V�[��");

	mp_mapActor = GameActor::createMap(ofApp::getInstance()->hierarchyRoot_.get(), { 0.f, 0.f, 0.f });
	auto mapCpnt = mp_mapActor->getComponent<MapComponent>();
	mapCpnt->CreateRandomMap();
	mapCpnt->CreateStepActor();
	//mp_mapActor->getComponent<MapComponent>()->LoadMap("data/map1.csv");
	//mp_mapActor->getComponent<MapComponent>()->LoadMap("data/Book1.csv");
	*m_prmInState = _pprm;

}
GameState * GameStateMap::update()
{
	auto mapCpnt = mp_mapActor->getComponent<MapComponent>();
	auto kind = mapCpnt->GetResKind();
	switch (kind)
	{
	case MapComponent::StepKind::EVENT:
		return &GameMainCtrlComponent::m_gameStateTitle;
		break;
	case MapComponent::StepKind::BATTLE:
		return &GameMainCtrlComponent::m_gameStateBattle;
	case MapComponent::StepKind::GOAL:
		mapCpnt->ClearMap();
		return &GameMainCtrlComponent::m_gameStateTitle;
		break;
	default:
		break;
	}
	return nullptr;
}

void GameStateMap::exit(Parameter& _pprm)
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild<GameActor>();
	_pprm = *m_prmInState;
}


void GameStateBattle::enter(Parameter _pprm)
{
	mp_fontActor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	mp_fontActor->Pos() = { (float)Define::WIN_W / 2, (float)Define::WIN_H / 2 };
	mp_fontActor->addComponent<FontRendererComponent>()->
		initialize(u8"�퓬�V�[��");

	*m_prmInState = _pprm;
	m_prmInState->getPlayerParam("HP");

	mp_actor2 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	mp_actor2->Pos() = { 500,300 };
	mp_actor2->addComponent<FontRendererComponent>()->
		initialize(ofToString(0));

	// �퓬�V�X�e��������
	mp_BattleComp = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>()->addComponent<BattleComponent>();
	//mp_Player = ofApp::getInstance()->hierarchyRoot_->addChild<PlayerActor>();
	m_EnemyList.emplace_back(ofApp::getInstance()->hierarchyRoot_->addChild<EnemyActor>());
	mp_BattleComp->SetPlayer(m_prmInState);
	mp_BattleComp->SetEnemy(m_EnemyList);
}

GameState * GameStateBattle::update()
{
	mp_actor2->getComponent<FontRendererComponent>()->String() = mp_BattleComp->GetInfo();

	// ���s�̌��ʂɉ����ăV�[���J��
	auto result = mp_BattleComp->GetResult();
	switch (result)
	{
	case BattleComponent::Result::WIN:
		return &GameMainCtrlComponent::m_gameStateTitle;
	case BattleComponent::Result::LOSE:
		return &GameMainCtrlComponent::m_gameStateTitle;
	default:
		break;
	}

	return nullptr;
}

void GameStateBattle::exit(Parameter& _pprm)
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild<GameActor>();
	ofApp::getInstance()->mp_soundManager->stop(0);
	m_EnemyList.clear();
	_pprm = *m_prmInState;
}

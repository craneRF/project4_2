#include "ofApp.h"
#include "GameState.h"
#include "GameActor.h"
#include "EnemyType.h"
#include "stdComponent.h"
#include "BattleHUD.h"
#include "LoadCSVFile.h"
#include "MapState.h"
#include "BattleState.h"
#include "CreateActor.h"

/*
* 1.hierarchyRoot_のGameMainCtrlComponent内でシーン制御をし、アクターの生成を行うことから、
*   GameMainCtrlComponentは常にActive状態であり、update()を行わなければならない。(hierarchyRoot_自体はActive状態でなくても良い)
* 2.GameMainCtrlComponentのupdate()内に存在するGameStateも常に行われるため、GameStateのupdate()も常に行われる。
* 3.GameStateのupdate()内で行われる「GameActor」・「UIActor」・「Coponentが持つインスタンス」のプロパティ(Actorでいうm_posやm_rotAngle、Pos()など)
*   に対する処理はそれぞれがどんな状態だろうが問答無用で行われる。
*
* 以上の3点とGameActor・UIActor・Component それぞれのState処理の都合上、
* GameStateのupdate()内では
* 「GameActor」・「UIActor」・「Coponentが持つインスタンス」のプロパティ(Actorでいうm_posやm_rotAngle、Pos()など)を変えないでください。
* もし変更が必要になったなら、直接的に変えるのではなく、それぞれのプロパティに影響のない変数を作って、そこから間接的にプロパティを変化させるようにしてください。
* 間接的に変更するのは面倒くさいし、ややこしくなるので非推奨。

* 例：
	・GameActorのプロパティの場合、それ専用のComponentを作り、そのComponentのupdate()内で変更する。
	・UIActorのプロパティの場合、それが存在しているUIScreenのupdate()内で変更する。
	・Componentが持つインスタンスのプロパティの場合、そのupdate()内で変更するか
	 もしくはそのComponentを持つGameActorのupdate()で変更する。

	※最終的に何が言いたいかというと、
	GameStateのupdate()内は極力シーン制御のみにし、
	例に書かれているような設計にしてください、ということです。
*/

void GameStateTitle::enter(Parameter _pprm)
{
	mp_fontActor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	mp_fontActor->Pos() = { (float)Define::FULLWIN_W / 5, (float)Define::FULLWIN_H / 5 };
	mp_fontActor->addComponent<FontRendererComponent>()->
		initialize(u8"タイトルシーン", 18);
	*m_prmInState = _pprm;

	ofApp::getInstance()->mp_soundManager->setVolume(0, 0.4f);
	ofApp::getInstance()->mp_soundManager->setVolume(1, 0.4f);
	ofApp::getInstance()->mp_soundManager->loop(0);

	// FPS表示
	//mp_actor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	//mp_actor->Pos() = { 500,100 };
	//mp_actor->addComponent<FontRendererComponent>()->
	//	initialize(ofToString(ofGetFrameRate()), 18, { 0,0,0 }, ofColor::white, {3, 3, 3}, "keifont.ttf");

	mp_actor1 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();

	//タイトル背景
	{
		auto spriteCpnt_bg = mp_actor1->addComponent<SpriteComponent>();
		spriteCpnt_bg->initialize("backGround_title_1.jpg");
	}

	//タイトルロゴ
	{
		auto spriteCpnt_title = mp_actor1->addComponent<SpriteComponent>();
		spriteCpnt_title->initialize("title.png");
		spriteCpnt_title->AlignPivotCenter();
		spriteCpnt_title->Offset() += {(float)Define::FULLWIN_W / 2, (float)Define::FULLWIN_H / 2 - 200.f};
	}

	mp_actor1->addComponent<FontRendererComponent>()->
		initialize(ofToString(m_prmInState->getPlayerParam("HP")), 18);

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

void GameStateTitle::exit(Parameter& _pprm)
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild<GameActor>();
	ofApp::getInstance()->mp_soundManager->stop(0);
	_pprm = *m_prmInState;
	ofApp::getInstance()->mp_soundManager->play(4);
}

void GameStateMap::enter(Parameter _pprm)
{

	mp_fontActor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	mp_fontActor->Pos() = { (float)Define::FULLWIN_W / 5, (float)Define::FULLWIN_H / 5 };
	//mp_fontActor->Pos() = { (float)Define::FULLWIN_W / 2, (float)Define::FULLWIN_H / 2 };
	mp_fontActor->addComponent<FontRendererComponent>()->
		initialize(u8"マップシーン");

	ofApp::getInstance()->mp_soundManager->loop(1);

	auto mapActor = GameActor::createMap(ofApp::getInstance()->hierarchyRoot_.get(), { 0.f, 0.f, 0.f });
	mp_mapComp = mapActor->getComponent<MapComponent>();
	mp_mapComp->Initialize();

	auto spriteCpnt_bg = mapActor->addComponent<SpriteComponent>();
	spriteCpnt_bg->initialize("backGround_map_2.jpg");

	*m_prmInState = _pprm;
}
GameState * GameStateMap::update()
{
	auto kind = mp_mapComp->GetResKind();
	switch (kind)
	{
	case StepKind::EVENT:
		return &GameMainCtrlComponent::m_gameStateTitle;
		break;
	case StepKind::BATTLE:
		return &GameMainCtrlComponent::m_gameStateBattle;
	case StepKind::GOAL:
		MapComponent::ClearMap();
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
	ofApp::getInstance()->mp_soundManager->stop(1);
}


void GameStateBattle::enter(Parameter _pprm)
{
	mp_fontActor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	mp_fontActor->Pos() = { (float)Define::FULLWIN_W / 5, (float)Define::FULLWIN_H / 5 };
	mp_fontActor->addComponent<FontRendererComponent>()->
		initialize(u8"戦闘シーン");

	*m_prmInState = _pprm;
	m_prmInState->getPlayerParam("HP");

	mp_actor2 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	mp_actor2->Pos() = { 500,300 };
	mp_actor2->addComponent<FontRendererComponent>()->
		initialize(ofToString(0));

	mp_BHUD = ofApp::getInstance()->addUICanvas<BattleHUD>();

	mp_actor2->findActor(mp_actor2, "");
	// 戦闘システム初期化
	{
		// 戦闘コンポーネント
		mp_BattleComp = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>()->addComponent<BattleComponent>();
		mp_BattleComp->SetPlayer(m_prmInState);
	}
}

GameState * GameStateBattle::update()
{
	mp_actor2->getComponent<FontRendererComponent>()->String() = mp_BattleComp->GetInfo();

	// 勝敗の結果に応じてシーン遷移
	auto result = mp_BattleComp->GetResult();
	switch (result)
	{
	case Result::WIN:
		return &GameMainCtrlComponent::m_gameStateMap;
	case Result::LOSE:
		MapComponent::ClearMap();
		return &GameMainCtrlComponent::m_gameStateTitle;
	default:
		break;
	}

	return nullptr;
}

void GameStateBattle::exit(Parameter& _pprm)
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild<GameActor>();
	ofApp::getInstance()->mp_soundManager->stop(2);
	//m_EnemyList.clear();
	_pprm = *m_prmInState;
	mp_BHUD->StateErace();
}

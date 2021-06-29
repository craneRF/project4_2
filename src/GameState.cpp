#include "ofApp.h"
#include "GameState.h"
#include "GameActor.h"
#include "EnemyType.h"
#include "stdComponent.h"
#include "LoadCSVFile.h"

//GameStateTitle
void GameStateTitle::enter(Parameter _pprm)
{
	mp_fontActor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	mp_fontActor->Pos() = { (float)Define::WIN_W / 2, (float)Define::WIN_H / 2 };
	mp_fontActor->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, u8"タイトルシーン", { }, ofColor::white);
	*m_prmInState = _pprm;

	//ofApp::getInstance()->mp_soundManager->setVolume(0, 0.4f);
	//ofApp::getInstance()->mp_soundManager->setVolume(1, 0.4f);
	//ofApp::getInstance()->mp_soundManager->loop(0);
	mp_actor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	mp_actor->Pos() = { 500,100 };
	mp_actor->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, ofToString(ofGetFrameRate()), { }, ofColor::white);

	mp_actor1 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	mp_actor1->Pos() = { 500,300 };
	mp_actor1->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, ofToString(m_prmInState->getPlayerParam("HP")), { }, ofColor::white);

	//PlayerActor::createPlayer(ofApp::getInstance()->hierarchyRoot_.get(), { 400,50 });
	//EnemyActor::createEnemy(ofApp::getInstance()->hierarchyRoot_.get(), { 200,50 },NONE);
}

GameState* GameStateTitle::update(float _deltatime)
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
		return &GameMainCtrlComponent::m_gameStateBattle;
	}
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
		initialize(ofApp::getInstance()->myFont, u8"マップシーン", { }, ofColor::white);

	mp_mapActor = GameActor::createMap(ofApp::getInstance()->hierarchyRoot_.get(), { 0.f, 0.f, 0.f });
	mp_mapActor->getComponent<MapComponent>()->LoadMap("data/Book1.csv");
	*m_prmInState = _pprm;

}
GameState * GameStateMap::update(float _deltatime)
{
	auto kind = mp_mapActor->getComponent<MapComponent>()->GetResKind();
	switch (kind)
	{
	case MapComponent::StepKind::EVENT:
		break;
	case MapComponent::StepKind::BATTLE:
		return &GameMainCtrlComponent::m_gameStateBattle;
	case MapComponent::StepKind::GOAL:
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
		initialize(ofApp::getInstance()->myFont, u8"戦闘シーン", { }, ofColor::white);

	*m_prmInState = _pprm;
	m_prmInState->getPlayerParam("HP");

	mp_actor2 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	mp_actor2->Pos() = { 500,300 };
	mp_actor2->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, ofToString(0), { }, ofColor::white);

	// 戦闘システム初期化
	mp_BattleComp = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>()->addComponent<BattleComponent>();
	mp_Player = ofApp::getInstance()->hierarchyRoot_->addChild<PlayerActor>();
	//ofApp::getInstance()->hierarchyRoot_->addChild<EnemyActor>();

	//m_EnemyList.emplace_back(ofApp::getInstance()->hierarchyRoot_->addChild<EnemyActor>());
	//PlayerActor::createPlayer(ofApp::getInstance()->hierarchyRoot_.get(), { 400,50 });

	m_EnemyList.emplace_back(EnemyActor::createEnemy(ofApp::getInstance()->hierarchyRoot_.get(), { 200,200 }, Nomal));
	//m_EnemyList.emplace_back(EnemyActor::createEnemy(ofApp::getInstance()->hierarchyRoot_.get(), { 800,50 }, Small));
	mp_BattleComp->SetPlayer(m_prmInState);
	mp_BattleComp->SetEnemy(m_EnemyList);
}

GameState * GameStateBattle::update(float _deltatime)
{
	mp_actor2->getComponent<FontRendererComponent>()->String() = mp_BattleComp->GetInfo();

	// 勝敗の結果に応じてシーン遷移
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

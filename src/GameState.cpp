#include "ofApp.h"
#include "GameState.h"
#include "GameActor.h"
#include "PlayerActor.h"
#include "EnemyActor.h"
#include "stdComponent.h"
#include "LoadCSVFile.h"

//GameStateTitle
void GameStateTitle::enter(Parameter _inportprm)
{
	m_prmInState = _inportprm;

	ofApp::getInstance()->mp_soundManager->setVolume(0, 0.4f);
	ofApp::getInstance()->mp_soundManager->setVolume(1, 0.4f);
	ofApp::getInstance()->mp_soundManager->loop(0);

	mp_actor = ofApp::getInstance()->hierarchyRoot_->addChild();
	mp_actor->Pos() = { 500,100 };
	mp_actor->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, ofToString(ofGetFrameRate()), { }, ofColor::white);

	mp_actor1 = ofApp::getInstance()->hierarchyRoot_->addChild();
	mp_actor1->Pos() = { 500,300 };
	mp_actor1->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, ofToString(m_prmInState.getPlayerParam("HP")), { }, ofColor::white);

	PlayerActor::createPlayer(ofApp::getInstance()->hierarchyRoot_.get(), { 400,50 });
	EnemyActor::createEnemy(ofApp::getInstance()->hierarchyRoot_.get(), { 300,50 });
}

GameState* GameStateTitle::update(float _deltatime)
{
	mp_actor->getComponent<FontRendererComponent>()->String() = ofToString(ofGetLastFrameTime()/*ofGetElapsedTimeMillis()*/);
	mp_actor1->getComponent<FontRendererComponent>()->String() = ofToString(m_prmInState.getPlayerParam("HP"));
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Fire")) {
		m_prmInState.setPlayerParam("HP", 50);
	}
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Bomb")) {
		m_prmInState.setPlayerParam("HP", 100);
	}
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
		return &GameMainCtrlComponent::m_gameStateMap;
	}
	return nullptr;
}

void GameStateTitle::exit(Parameter& _reprm)
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild();
	ofApp::getInstance()->mp_soundManager->stop(0);
	_reprm = m_prmInState;
}

//GameStateMap
void GameStateMap::enter(Parameter _inportprm)
{
	m_prmInState = _inportprm;

	mp_actor2 = ofApp::getInstance()->hierarchyRoot_->addChild();
	mp_actor2->Pos() = { 500,300 };
	mp_actor2->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, ofToString(m_prmInState.getPlayerParam("HP")), { }, ofColor::white);

	//mp_mapActor = GameActor::createMap(ofApp::getInstance()->hierarchyRoot_.get(), { 0.f, 0.f, 0.f });
	//mp_mapActor->getComponent<MapComponent>()->LoadMap("data/Book1.csv");
}

GameState* GameStateMap::update(float _deltatime)
{
	mp_actor2->getComponent<FontRendererComponent>()->String() = ofToString(m_prmInState.getPlayerParam("HP"));
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Fire")) {
		m_prmInState.setPlayerParam("HP", 50);
	}
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Bomb")) {
		m_prmInState.setPlayerParam("HP", 100);
	}
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
		return &GameMainCtrlComponent::m_gameStateTitle;
	}

	//auto kind = mp_mapActor->getComponent<MapComponent>()->GetResKind();
	//switch (kind)
	//{
	//case MapComponent::StepKind::EVENT:
	//	break;
	//case MapComponent::StepKind::BATTLE:
	//	return &GameMainCtrlComponent::m_gameStateBattle;
	//case MapComponent::StepKind::GOAL:
	//	break;
	//default:
	//	break;
	//}

	return nullptr;
	
}

void GameStateMap::exit(Parameter& _reprm)
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild();
	ofApp::getInstance()->mp_soundManager->stop(0);
	_reprm = m_prmInState;
}
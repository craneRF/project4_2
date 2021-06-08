#include "ofApp.h"
#include "GameState.h"
#include "GameActor.h"
#include "stdComponent.h"
#include "LoadCSVFile.h"

void GameStateTitle::enter()
{
	mp_fontActor = ofApp::getInstance()->hierarchyRoot_->addChild();
	mp_fontActor->Pos() = { (float)Define::WIN_W / 2, (float)Define::WIN_H / 2 };
	mp_fontActor->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, u8"タイトルシーン", { }, ofColor::white);
}

GameState* GameStateTitle::update(float _deltatime)
{
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
		return &GameMainCtrlComponent::m_gameStateMap;
	}
	else if (ofApp::getInstance()->mp_inputManager->getButtonDown("Fire"))
	{
		return &GameMainCtrlComponent::m_gameStateBattle;
	}
	return nullptr;
}

void GameStateTitle::exit()
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild();
}

void GameStateMap::enter()
{
	mp_fontActor = ofApp::getInstance()->hierarchyRoot_->addChild();
	mp_fontActor->Pos() = { (float)Define::WIN_W / 2, (float)Define::WIN_H / 2 };
	mp_fontActor->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, u8"マップシーン", { }, ofColor::white);

	mp_mapActor = GameActor::createMap(ofApp::getInstance()->hierarchyRoot_.get(), { 0.f, 0.f, 0.f });
	mp_mapActor->getComponent<MapComponent>()->LoadMap("data/Book1.csv");
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

void GameStateMap::exit()
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild();
}

void GameStateBattle::enter()
{
	mp_fontActor = ofApp::getInstance()->hierarchyRoot_->addChild();
	mp_fontActor->Pos() = { (float)Define::WIN_W / 2, (float)Define::WIN_H / 2 };
	mp_fontActor->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, u8"戦闘シーン", { }, ofColor::white);

}

GameState * GameStateBattle::update(float _deltatime)
{
	return nullptr;
}

void GameStateBattle::exit()
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild();
}

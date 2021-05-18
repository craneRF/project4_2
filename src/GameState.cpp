#include "ofApp.h"
#include "GameState.h"
#include "GameActor.h"
#include "FontRendererComponent.h"
#include "LoadCSVFile.h"

void GameStateTitle::enter()
{
	/*auto actor = ofApp::getInstance()->hierarchyRoot_->addChild();
	actor->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, "SHOOTING GAME", { 100,100 }, ofColor::black);*/

	mp_actor = ofApp::getInstance()->hierarchyRoot_->addChild();
	mp_actor->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, ofToString(ofGetLastFrameTime()), { 100,100 }, ofColor::white);
	string u0 = u8"hello";
	mp_actor1 = ofApp::getInstance()->hierarchyRoot_->addChild();
	mp_actor1->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, u0, { 0,100 }, ofColor::white);

	GameActor::createPlayer(ofApp::getInstance()->hierarchyRoot_.get(), { 400,50 });
	GameActor::createEnemy(ofApp::getInstance()->hierarchyRoot_.get(), { 300,50 });
	/*vector<vector<string>> hololivemembertable;
	LoadCSVFile csv("data/3Šú¶ƒzƒƒƒ“.csv", hololivemembertable);

	for (int r = 0; r < hololivemembertable.size(); r++)
	{
		for (int i = 0; i < hololivemembertable.at(r).size(); i++)
		{
			GameActor* mp_actor = ofApp::getInstance()->hierarchyRoot_->addChild();
			mp_actor->addComponent<FontRendererComponent>()->
				initialize(ofApp::getInstance()->myFont, hololivemembertable.at(r).at(i), { 150.f * (i + 1),50.f * (r + 1) }, ofColor::white);
		}
	}*/
	//auto actor1 = ofApp::getInstance()->hierarchyRoot_->addChild();
	//actor1->Pos() = { 200,300,0 };
	//auto spr1 = actor1->addComponent<SpriteComponent>();
	//spr1->setImage(ofApp::getInstance()->imagesManager_->getContents("Images/Idling/U_0000.png"));
	//spr1->offset() = { -64,-64 };
	//actor1->Scale() = { 1.5f,1.5f };
	//actor1->RotAngle() = 30;
	//auto actor2 = ofApp::getInstance()->hierarchyRoot_->addChild();
	//actor2->Pos() = { 300,300,1 };
	//auto spr2 = actor2->addComponent<SpriteComponent>();
	//spr2->setImage(ofApp::getInstance()->imagesManager_->getContents("Images/Running/D_0000.png"));
	//spr2->offset() = { -64,-64 };
	////auto animseq = new AnimSeq("animseq/AnimSeqWalkUp.json");
	//auto animseq = ofApp::getInstance()->animSeqManager_->getContents("animseq/AnimSeqWalkUp.json");
	////actor2->addComponent<AnimationComponent>()->initialize(animseq);
	//actor2->addComponent<AnimationComponent>()->initialize(animseq);
	//auto actor3 = ofApp::getInstance()->hierarchyRoot_->addChild();
	//actor3->Pos() = { 200,32,0 };
	//actor3->RotAngle() = 0;
	//actor3->Scale() = { 1.0f,1.0f };
	//actor3->Name() = "tile01";
	//actor3->addComponent<TileMapComponent>()->initialize("TileData/TileDef01.txt", "MapData/map02.csv");
}

GameState* GameStateTitle::update(float _deltatime)
{
	mp_actor->getComponent<FontRendererComponent>()->String() = ofToString(ofGetLastFrameTime()/*ofGetElapsedTimeMillis()*/);

	//if (ofApp::getInstance()->inputManager_->getButtonDown("Start")) {
	//	return &GameMainCtrlComponent::gameStateMain_;
	//}
	return nullptr;
}

void GameStateTitle::exit()
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild();
}
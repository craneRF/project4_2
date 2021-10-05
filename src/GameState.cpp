#include "ofApp.h"
#include "GameState.h"
#include "GameActor.h"
#include "stdComponent.h"
#include "BattleHUD.h"
#include "LoadCSVFile.h"

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

void GameStateTitle::enter()
{
	/*auto actor = ofApp::getInstance()->hierarchyRoot_->addChild();
	actor->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, "SHOOTING GAME", { 100,100 }, ofColor::black);*/
	/*ofApp::getInstance()->mp_soundManager->setVolume(0, 0.4f);
	ofApp::getInstance()->mp_soundManager->setVolume(1, 0.4f);
	ofApp::getInstance()->mp_soundManager->loop(0);*/

	mp_actor = ofApp::getInstance()->hierarchyRoot_->addChild();
	mp_actor->Pos() = { 700,100 };
	mp_actor->addComponent<FontRendererComponent>()->
		initialize(ofToString(ofGetFrameRate()), 18, { 0,0,0 }, ofColor::white, {3, 3, 3}, "keifont.ttf");
	//"keifont.ttf"

	//string u0 = u8"hello";
	//mp_actor1 = ofApp::getInstance()->hierarchyRoot_->addChild();
	//mp_actor1->Pos() = { 50, 100 };
	//mp_actor1->addComponent<FontRendererComponent>()->
	//	initialize(/*ofToString(*/mp_actor->getComponent<FontRendererComponent>()->String(), 18, { 0,100,0 }, ofColor::red, {1, 1, 1}, "keifont.ttf");

	GameActor::createPlayer(ofApp::getInstance()->hierarchyRoot_.get(), { 400,50 });
	mp_Enemy = GameActor::createEnemy(ofApp::getInstance()->hierarchyRoot_.get(), { 300,50 });
	
	//auto mp_actor2 = ofApp::getInstance()->hierarchyRoot_->addChild();"Images/Idling/marine_icon.png"

	mp_actor2 = ofApp::getInstance()->hierarchyRoot_->addChild();
	mp_actor2->Pos() = { 700, 450, 0 };
	mp_actor2->Scale() = { 0.25f, 0.25f };
	auto spr1 = mp_actor2->addComponent<SpriteComponent>();
	spr1->initialize("Arrow.png");
	spr1->AlignPivotCenter();
	m_move = mp_actor2->addComponent<MoveComponent>();

	vector<vector<string>> hololivemembertable;
	LoadCSVFile::SetTable("data/3期生ホロメン.csv", hololivemembertable);

	auto mp_actor3 = ofApp::getInstance()->hierarchyRoot_->addChild();
	for (int r = 0; r < hololivemembertable.size(); r++) {
		for (int i = 0; i < hololivemembertable.at(r).size(); i++) {
			mp_actor3 = ofApp::getInstance()->hierarchyRoot_->addChild();
			mp_actor3->addComponent<FontRendererComponent>()->
				initialize(hololivemembertable.at(r).at(i), 18, { 150.f * (i + 1),100.f * (r + 1) }, ofColor::white, {1, 1, 1});
		}
	}

	mp_BHUD = ofApp::getInstance()->addUICanvas<BattleHUD>();

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
	mp_actor->getComponent<FontRendererComponent>()->String() = ofToString(ofGetLastFrameTime());
	mp_actor->getComponent<FontRendererComponent>()->Scale() = ofVec3f(ofGetLastFrameTime() * 100, ofGetLastFrameTime() * 100, 1);

	mp_Enemy->getComponent<MoveComponent>()->AddMovePos({ 50.0f, 0.0f, 0.0f });

	/*if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
		return &GameMainCtrlComponent::m_gameStateMain;
	}*/
	if (ofApp::getInstance()->mp_inputManager->getButtonHold("Start")) {
		/*ofApp::getInstance()->mp_soundManager->play(1);
		if (mp_actor2->GetActorState() == Actor::ActorState::EPause) {
			mp_actor2->StateActive();
			mp_actor2->StateAllCpntActive();
		}
		else {
			mp_actor2->StatePause();
			mp_actor2->StateAllCpntPause();
		}*/
		m_move->FrontMove(200.0f);
	}
	else {
		m_move->AddMoveAngle(180.0f);
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
	return nullptr;
}

void GameStateTitle::exit()
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild();
	ofApp::getInstance()->mp_soundManager->stop(0);
}
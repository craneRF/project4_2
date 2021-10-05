#include "ofApp.h"
#include "GameState.h"
#include "GameActor.h"
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
	LoadCSVFile::SetTable("data/3�����z������.csv", hololivemembertable);

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
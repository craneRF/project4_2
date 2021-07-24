#include "ofApp.h"
#include "stdComponent.h"
#include "GameMainCtrlComponent.h"
#include "UIScreen.h"

ofApp* ofApp::instance = nullptr;

ofApp* ofApp::getInstance() {
	assert(instance);
	return instance;
}

//--------------------------------------------------------------
void ofApp::setup() {

	instance = this;

	mp_font = make_unique<Font>();
	mp_texture = make_unique<Texture>();

	mp_collisionManager = make_unique<CollisionManager>();
	mp_soundManager = make_unique<SoundManager>();
	mp_inputManager = make_unique<InputManager>();

	m_deltaTime = 0.0f;

	hierarchyRoot_ = make_unique<GameActor>();
	hierarchyRoot_->mp_parent = nullptr;
	hierarchyRoot_->Pos() = { 0, 0, 0 };
	hierarchyRoot_->Name() = "World";

	/*GameActor::createPlayer(getInstance()->hierarchyRoot_.get(), { 400,50 });
	GameActor::createEnemy(getInstance()->hierarchyRoot_.get(), { 300,50 });*/

	//auto act1 = GameActor::createPlayer(getInstance()->hierarchyRoot_.get(), { 300,50 });
	//auto movevcpnt = act1->getComponent<MoveComponent>();
	//movevcpnt->setMoveVec({ 1,0,0 });
	//auto colcpnt = act1->getComponent<CollisionComponent>();
	//colcpnt->initialize(ofVec3f(0, 0), 30, 30, CollisionType::ENEMY_OBJECT);
	//GameActor::createEnemy(getInstance()->hierarchyRoot_.get(), { 300,50 });

	mp_gameMainCtrlComponent = hierarchyRoot_->addComponent<GameMainCtrlComponent>();
	mp_gameMainCtrlComponent->GameStateStart();
}

//--------------------------------------------------------------
void ofApp::update() {

	mp_collisionManager->CaluculateCollision();
	mp_inputManager->update();

	m_deltaTime = ofGetLastFrameTime();
	//if (m_deltaTime > 0.5f) { m_deltaTime = 0.5f; }
	if (m_deltaTime < 1 / 60.f) { m_deltaTime = 1 / 60.f; }

	for (int i = 0; i < (int)(60 * m_deltaTime); i++) {

		if (hierarchyRoot_->GetActorState() != Actor::ActorState::EPause) {
			if (hierarchyRoot_->GetActorState() == Actor::ActorState::EActive) {
				hierarchyRoot_->input(m_deltaTime);  //hierarchyRoot_がEActive状態なら行う
			}
			hierarchyRoot_->update(m_deltaTime);  //hierarchyRoot_がEPause状態でないなら行う
		}
		

		//追加待ちUIScreenの追加処理
		while (!m_UIScreenAddQue.empty()) {
			m_UIScreenStack.push_back(move(m_UIScreenAddQue.front()));
			m_UIScreenAddQue.pop();
		}

		for (auto iter = m_UIScreenStack.begin(); iter != m_UIScreenStack.end();) {
			if ((*iter)->GetUIScreenState() == UIScreen::UIScreenState::EErace) {
				//delete *iter;
				iter = m_UIScreenStack.erase(iter);  //EErace状態のUIScreenを削除し、その後のイテレーター全てを前に持ってくる
			}
			else {
				++iter;
			}
		}

		if (!m_UIScreenStack.empty()) {
			for (auto& ui : m_UIScreenStack)
			{
				if (ui->GetUIScreenState() != UIScreen::UIScreenState::EPause) {
					if (ui->GetUIScreenState() == UIScreen::UIScreenState::EActive) {
						ui->input(m_deltaTime);  //操作処理はEActive状態の時しか行わない
					}
					ui->update(m_deltaTime);  //操作処理以外はEActive状態とEUnControl状態の時に行う
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	if (hierarchyRoot_->GetActorDrawState() == Actor::ActorDrawState::EVisible) {
		hierarchyRoot_->draw();
	}

	if (!m_UIScreenStack.empty()) {
		for (auto& ui : m_UIScreenStack) {
			if (ui->GetUIScreenDrawState() == UIScreen::UIScreenDrawState::EVisible) {
				ui->draw();  //Visible状態のUIScreenを描画
			}
		}
	}
	//ofPushMatrix();
	//ofSetColor(ofColor::white);
	//for (auto c : draworderset_) {
	//	c->draw();
	//}
	//ofPopMatrix();
}
void ofApp::exit()
{
	mp_font.reset();
	mp_texture.reset();

	hierarchyRoot_.reset();
	m_UIScreenStack.clear();

	mp_collisionManager.reset();
	mp_soundManager.reset();
	mp_inputManager.reset();

	//while (!m_UIScreenStack.empty()) {
	//	delete m_UIScreenStack.back();  //m_UIScreenのスタックを削除
	//	m_UIScreenStack.pop_back();
	//}
}

UIScreen* ofApp::addUIScreen(string _name, UIPanelCanvas* _canvas)
{
	auto screen = make_unique<UIScreen>(_name, _canvas);
	auto res = screen.get();
	m_UIScreenAddQue.push(move(screen));
	return res;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

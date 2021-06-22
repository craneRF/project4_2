#include "ofApp.h"
#include "stdComponent.h"
#include "GameMainCtrlComponent.h"

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
	hierarchyRoot_->initialize({ 0,0 }, "World");

	/*GameActor::createPlayer(getInstance()->hierarchyRoot_.get(), { 400,50 });
	GameActor::createEnemy(getInstance()->hierarchyRoot_.get(), { 300,50 });*/

	//auto act1 = GameActor::createPlayer(getInstance()->hierarchyRoot_.get(), { 300,50 });
	//auto movevcpnt = act1->getComponent<MoveComponent>();
	//movevcpnt->setMoveVec({ 1,0,0 });
	//auto colcpnt = act1->getComponent<CollisionComponent>();
	//colcpnt->initialize(ofVec3f(0, 0), 30, 30, CollisionType::ENEMY_OBJECT);
	//GameActor::createEnemy(getInstance()->hierarchyRoot_.get(), { 300,50 });

	mp_gameMainCtrlComponent = hierarchyRoot_->addComponent<GameMainCtrlComponent>();
	//mp_gameMainCtrlComponent->playerScore_ = 0;
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
		hierarchyRoot_->update(m_deltaTime);
	}
	//hierarchyRoot_->update(m_deltaTime);

	for (auto& ui : m_UIStack)
	{
		if (ui->GetUIActorState() != UIActor::UIActorState::EDrew && ui->GetUIActorState() != UIActor::UIActorState::EClosing) {
			if (ui->GetUIActorState() == UIActor::UIActorState::EActive) {
				ui->input(m_deltaTime);  //‘€ìˆ—‚ÍEActiveó‘Ô‚ÌUIScreen‚µ‚©s‚í‚È‚¢
			}
			ui->update(m_deltaTime);  //•`‰æ‚É‰e‹¿‚·‚éˆ—‚È‚Ç‚ÍEActiveó‘Ô‚ÆEDrawingó‘Ô‚ÌŽž‚És‚¤
		}
	}

	for (auto iter = m_UIStack.begin(); iter != m_UIStack.end();) {
		if ((*iter)->GetUIActorState() == UIActor::UIActorState::EClosing) {
			iter = m_UIStack.erase(iter);
		}
		else {
			++iter;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	hierarchyRoot_->draw(m_deltaTime);

	for (auto& ui : m_UIStack) {
		ui->draw(m_deltaTime);
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
	hierarchyRoot_.reset();
	mp_collisionManager.reset();
	mp_soundManager.reset();
	mp_inputManager.reset();
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

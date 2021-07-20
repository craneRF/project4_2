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

	hierarchyRoot_->getComponent<GameMainCtrlComponent>()->StateCpntActive();  //GameMainCtrlComponent�͏��Active���

	m_deltaTime = ofGetLastFrameTime();
	//if (m_deltaTime > 0.5f) { m_deltaTime = 0.5f; }
	if (m_deltaTime < 1 / 60.f) { m_deltaTime = 1 / 60.f; }
	for (int i = 0; i < (int)(60 * m_deltaTime); i++) {
		hierarchyRoot_->update(m_deltaTime);
		hierarchyRoot_->input(m_deltaTime);

		//�ǉ��҂�UIScreen�̒ǉ�����
		while (!m_UIScreenAddQue.empty()) {
			m_UIScreenStack.push_back(move(m_UIScreenAddQue.front()));
			m_UIScreenAddQue.pop();
		}

		for (auto iter = m_UIScreenStack.begin(); iter != m_UIScreenStack.end();) {
			if ((*iter)->GetUIScreenState() == UIScreen::UIScreenState::EErace) {
				//delete *iter;
				iter = m_UIScreenStack.erase(iter);  //EErace��Ԃ�UIScreen���폜���A���̌�̃C�e���[�^�[�S�Ă�O�Ɏ����Ă���
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
						ui->input(m_deltaTime);  //���쏈����EActive��Ԃ̎������s��Ȃ�
					}
					ui->update(m_deltaTime);  //���쏈���ȊO��EActive��Ԃ�EUnControl��Ԃ̎��ɍs��
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	hierarchyRoot_->draw();

	if (!m_UIScreenStack.empty()) {
		for (auto& ui : m_UIScreenStack) {
			if (ui->GetUIScreenDrawState() == UIScreen::UIScreenDrawState::EVisible) {
				ui->draw();  //Visible��Ԃ�UIScreen��`��
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
	//	delete m_UIScreenStack.back();  //m_UIScreen�̃X�^�b�N���폜
	//	m_UIScreenStack.pop_back();
	//}
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

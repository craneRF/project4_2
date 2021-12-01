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
	hierarchyRoot_->Pos() = { 0, 0, 0 };
	hierarchyRoot_->Name() = "World";

	mp_gameMainCtrlComponent = hierarchyRoot_->addComponent<GameMainCtrlComponent>();
	mp_gameMainCtrlComponent->GameStateStart();

	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();
	windowScale = 1.0f;
	widthScaled = windowWidth * windowScale;
	heightScaled = windowHeight * windowScale;
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
				hierarchyRoot_->input();  //hierarchyRoot_がEActive状態なら行う
			}
			hierarchyRoot_->update();  //hierarchyRoot_がEPause状態でないなら行う
		}
	

		//追加待ちUIScreenの追加処理
		while (!m_UIPanelAddQue.empty()) {
			m_UIPanelStack.push_back(move(m_UIPanelAddQue.front()));
			m_UIPanelAddQue.pop();
		}

		for (auto iter = m_UIPanelStack.begin(); iter != m_UIPanelStack.end();) {
			if ((*iter)->GetActorState() == Actor::ActorState::EErace) {
				//delete *iter;
				iter = m_UIPanelStack.erase(iter);  //EErace状態のUIScreenを削除し、その後のイテレーター全てを前に持ってくる
			}
			else {
				++iter;
			}
		}

		if (!m_UIPanelStack.empty()) {
			for (auto& ui : m_UIPanelStack)
			{
				if (ui->GetActorState() != Actor::ActorState::EPause) {
					if (ui->GetActorState() == Actor::ActorState::EActive) {
						ui->input();  //操作処理はEActive状態の時しか行わない
					}
					ui->update();  //操作処理以外はEActive状態とEUnControl状態の時に行う
				}
			}
		}
	}

	if (bScaleDirFixed) {
		bScaleDirFixed = false;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	if (hierarchyRoot_->GetActorDrawState() == Actor::ActorDrawState::EVisible) {
		hierarchyRoot_->draw();
	}

	if (!m_UIPanelStack.empty()) {
		for (auto& ui : m_UIPanelStack) {
			if (ui->GetActorDrawState() == Actor::ActorDrawState::EVisible) {
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
	m_UIPanelStack.clear();

	mp_collisionManager.reset();
	mp_soundManager.reset();
	mp_inputManager.reset();
}

//UIScreen* ofApp::addUIScreen(string _name, UIPanelCanvas* _canvas)
//{
//	auto screen = make_unique<UIScreen>(_name, _canvas);
//	auto res = screen.get();
//	m_UIPanelAddQue.push(move(screen));
//	return res;
//}

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
	if (!bScaleDirFixed) {

		int gapW = abs(widthScaled - w);
		int gapH = abs(heightScaled - h);

		if (gapW > gapH)
			scaleDir = SCALE_DIR_HORIZONTAL;
		else
			scaleDir = SCALE_DIR_VERTICAL;
		bScaleDirFixed = true;
	}
	float ratio;

	if (scaleDir == SCALE_DIR_HORIZONTAL) {

		ratio = static_cast<float>(windowHeight) / static_cast<float>(windowWidth);
		h = w * ratio;
		windowScale = static_cast<float>(w) / static_cast<float>(windowWidth);
	}
	else if (scaleDir == SCALE_DIR_VERTICAL) {

		ratio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
		w = h * ratio;
		windowScale = static_cast<float>(h) / static_cast<float>(windowHeight);
	}
	widthScaled = windowWidth * windowScale;
	heightScaled = windowHeight * windowScale;
	ofSetWindowShape(widthScaled, heightScaled);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

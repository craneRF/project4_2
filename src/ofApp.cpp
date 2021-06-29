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

	mp_collisionManager = make_unique<CollisionManager>();
	mp_soundManager = make_unique<SoundManager>();
	mp_inputManager = make_unique<InputManager>();

	mp_imageManager = make_unique<ResourceManager<ofImage>>();
	mp_imageManager->loadContentFromFile("ImageRes.txt");


	m_deltaTime = 0.0f;

	hierarchyRoot_ = make_unique<GameActor>();
	hierarchyRoot_->mp_parent = nullptr;
	hierarchyRoot_->initialize({ 0,0 }, "World");

	//auto fontsettings = ofTrueTypeFontSettings("mplus-1p-regular.ttf", 16);
	auto fontsettings = ofTrueTypeFontSettings("keifont.ttf", 16);
	fontsettings.addRanges(ofAlphabet::Latin);
	fontsettings.addRanges(ofAlphabet::Japanese);
	myFont.load(fontsettings);

	mp_gameMainCtrlComponent = hierarchyRoot_->addComponent<GameMainCtrlComponent>();
	//mp_gameMainCtrlComponent->playerScore_ = 0;
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
		hierarchyRoot_->update(m_deltaTime);
	}
	//hierarchyRoot_->update(m_deltaTime);

	if (bScaleDirFixed) {
		bScaleDirFixed = false;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	hierarchyRoot_->draw(m_deltaTime);
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

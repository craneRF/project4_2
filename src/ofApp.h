#pragma once

#include "ofMain.h"
#include "Define.h"
#include "Parameter.h"
#include "GameActor.h"
#include "stdMgr.h"

enum ScaleDir { //window scaling directions

	SCALE_DIR_HORIZONTAL,
	SCALE_DIR_VERTICAL,
};

class GameMainCtrlComponent;

class ofApp : public ofBaseApp {
private:
	static ofApp* instance;

public:
	static ofApp* getInstance();

	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	float m_deltaTime;
	uint32_t m_TicksCount;

	ofTrueTypeFont myFont;

	unique_ptr<GameActor> hierarchyRoot_;

	unique_ptr< CollisionManager> mp_collisionManager;
	unique_ptr< SoundManager> mp_soundManager;
	unique_ptr< InputManager> mp_inputManager;

	unique_ptr< ResourceManager<ofImage>> mp_imageManager;
	GameMainCtrlComponent* mp_gameMainCtrlComponent;

	ScaleDir scaleDir;

	int windowWidth, windowHeight; //original window dimensions
	float widthScaled, heightScaled; //scaled window dimensions
	float windowScale; //scale amount (1.0 = original)
	bool bScaleDirFixed; //is direction fixed?
};


#pragma once

#include "ofMain.h"
#include "Define.h"
#include "GameActor.h"
#include "CollisionManager.h"


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

	GameMainCtrlComponent* mp_gameMainCtrlComponent;
};

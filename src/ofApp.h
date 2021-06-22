#pragma once

#include "ofMain.h"
#include "Define.h"
#include "GameActor.h"
#include "stdMgr.h"
#include "Font.h"
#include "Texture.h"
#include "UIActor.h"

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

	unique_ptr<Font> mp_font;
	unique_ptr<Texture> mp_texture;
	

	unique_ptr<GameActor> hierarchyRoot_;

	unique_ptr< CollisionManager> mp_collisionManager;
	unique_ptr< SoundManager> mp_soundManager;
	unique_ptr< InputManager> mp_inputManager;


	std::vector<shared_ptr<UIActor>> m_UIStack;  //hierarchyRoot_ÇÃUIî≈Çäiî[Ç∑ÇÈïœêî
	const std::vector<shared_ptr<UIActor>>& GetUIStack() { return m_UIStack; }
	void PushUI(shared_ptr<UIActor> screen);

	GameMainCtrlComponent* mp_gameMainCtrlComponent;
};
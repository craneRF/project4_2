#pragma once

#include "ofMain.h"
#include "Define.h"
#include "GameActor.h"
#include "stdMgr.h"
#include "Font.h"
#include "Texture.h"
#include "UIScreen.h"

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
	vector<unique_ptr<UIScreen>> m_UIScreenStack;  //hierarchyRoot_‚ÌUI”Å‚ðŠi”[‚·‚é”z—ñ

	unique_ptr< CollisionManager> mp_collisionManager;
	unique_ptr< SoundManager> mp_soundManager;
	unique_ptr< InputManager> mp_inputManager;

	GameMainCtrlComponent* mp_gameMainCtrlComponent;

	inline const vector<unique_ptr<UIScreen>>& GetUIScreenStack() 
	{ 
		return m_UIScreenStack; 
	}
	inline void PushUIScreen(UIScreen* _screen)
	{
		m_UIScreenStack.emplace_back(_screen);
	}
};
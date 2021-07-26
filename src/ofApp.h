#pragma once

#include "ofMain.h"
#include "Define.h"
#include "GameActor.h"
#include "stdMgr.h"
#include "Font.h"
#include "Texture.h"
#include "UIScreen.h"
#include "UIPanelCanvas.h"

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

	//UIScreen* addUIScreen(string _name ="", UIPanelCanvas* _canvas = nullptr);

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
	queue<unique_ptr<UIScreen>> m_UIScreenAddQue;

	//vector<unique_ptr<UIPanelCanvas>> m_UIScreenStack;  //hierarchyRoot_‚ÌUI”Å‚ðŠi”[‚·‚é”z—ñ
	//queue<unique_ptr<UIPanelCanvas>> m_UIScreenAddQue;

	unique_ptr< CollisionManager> mp_collisionManager;
	unique_ptr< SoundManager> mp_soundManager;
	unique_ptr< InputManager> mp_inputManager;

	GameMainCtrlComponent* mp_gameMainCtrlComponent;

	/*inline const vector<unique_ptr<UIScreen>>& GetUIScreenStack()
	{ 
		return m_UIScreenStack; 
	}*/

	template <typename T>
	inline UIScreen* addUIScreen(string _name)
	{
		auto screen = make_unique<UIScreen>(_name);
		//auto canvas = make_unique<T>();
		screen->mp_Canvas = make_unique<T>();
		//screen->mp_Canvas = canvas.get();
		screen->mp_Canvas->SetParam();
		screen->mp_Canvas->mp_UIPanelParent = nullptr;
		screen->mp_Canvas->mp_UIScreenParent = screen.get();
		auto res = screen.get();
		m_UIScreenAddQue.push(move(screen));
		return res;
		/*cout << "UIPanelCanvas‚Ì”h¶ƒNƒ‰ƒX‚ð‘I‘ð‚µ‚Ä‚­‚¾‚³‚¢" << endl;
		return nullptr;*/
	}

	/*template <typename T>
	inline UIPanelCanvas* addUIScreen(string _name)
	{
		auto canvas = make_unique<T>(_name);
		canvas->SetParam();
		canvas->mp_UIPanelParent = nullptr;
		auto res = canvas.get();
		m_UIScreenAddQue.push(move(canvas));
		return res;
	}*/

	//template<>
	//inline UIScreen* addUIScreen<UIPanelCanvas>(string _name)
	//{
	//	auto screen = make_unique<UIScreen>(_name);
	//	auto canvas = make_unique<UIPanelCanvas>();
	//	screen->mp_Canvas = canvas.get();
	//	screen->mp_Canvas->mp_UIPanelParent = nullptr;
	//	screen->mp_Canvas->mp_UIScreenParent = screen.get();
	//	auto res = screen.get();
	//	m_UIScreenAddQue.push(move(screen));
	//	return res;
	//}
};
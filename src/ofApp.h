#pragma once

#include "ofMain.h"
#include "Define.h"
#include "Parameter.h"
#include "GameActor.h"
#include "stdMgr.h"
#include "Font.h"
#include "Texture.h"
#include "UIPanelCanvas.h"

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
	//vector<unique_ptr<UIScreen>> m_UIPanelStack;  //hierarchyRoot_‚ÌUI”Å‚ðŠi”[‚·‚é”z—ñ
	//queue<unique_ptr<UIScreen>> m_UIPanelAddQue;

	vector<unique_ptr<UIPanelCanvas>> m_UIPanelStack;  //hierarchyRoot_‚ÌUI”Å‚ðŠi”[‚·‚é”z—ñ
	queue<unique_ptr<UIPanelCanvas>> m_UIPanelAddQue;

	unique_ptr< CollisionManager> mp_collisionManager;
	unique_ptr< SoundManager> mp_soundManager;
	unique_ptr< InputManager> mp_inputManager;
	unique_ptr< ResourceManager<ofImage>> mp_imageManager;
	
	unique_ptr<Parameter>mp_prm;
	unique_ptr<ItemManager> mp_itemManager;

	GameMainCtrlComponent* mp_gameMainCtrlComponent;

	template <typename T>
	inline UIPanelCanvas* addUICanvas()
	{
		auto canvas = make_unique<T>();
		canvas->SetParam();
		canvas->mp_UIPanelParent = nullptr;
		canvas->mp_UICanvasParent = canvas.get();
		auto res = canvas.get();
		m_UIPanelAddQue.push(move(canvas));
		return res;
	}

	ScaleDir scaleDir;

	int windowWidth, windowHeight; //original window dimensions
	float widthScaled, heightScaled; //scaled window dimensions
	float windowScale; //scale amount (1.0 = original)
	bool bScaleDirFixed; //is direction fixed?
};


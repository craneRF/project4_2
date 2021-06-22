//#pragma once
//#include "ofMain.h"
//#include "UIActor.h"
//
//class UIScreen
//{
//public:
//	enum class UIState {
//		EActive  //描画処理・描画を動かす処理・操作処理の全てを行う
//		,EDrawing  //描画処理・描画を動かす処理を行う
//		,EDrew  //描画処理のみ行う(描画はされるが動かない)
//		,EClosing  //閉じられる()
//	};
//
//	UIScreen();
//	virtual ~UIScreen();
//
//	void update(float _deltaTime);
//	void input(float _deltaTime);
//	void draw(float _deltaTime);
//
//	void Close();
//	UIActor* addUIChild();
//
//	UIActor* mp_UIparent;
//	
//protected:
//	UIState m_UIState;
//
//	vector<unique_ptr<UIActor>> m_UIchildList;
//	queue<unique_ptr<UIActor>> m_UIchildAddQue;
//
//public:
//	inline const UIState GetUIState()
//	{ 
//		return m_UIState;
//	}
//};


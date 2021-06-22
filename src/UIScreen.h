//#pragma once
//#include "ofMain.h"
//#include "UIActor.h"
//
//class UIScreen
//{
//public:
//	enum class UIState {
//		EActive  //�`�揈���E�`��𓮂��������E���쏈���̑S�Ă��s��
//		,EDrawing  //�`�揈���E�`��𓮂����������s��
//		,EDrew  //�`�揈���̂ݍs��(�`��͂���邪�����Ȃ�)
//		,EClosing  //������()
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


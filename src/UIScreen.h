#pragma once
#include "ofMain.h"
//#include "UIActor.h"
#include "UIPanelCanvas.h"

//class UIPanelCanvas;

/*
* UI��hierarchyRoot_�̗l�Ȃ���
*/
class UIScreen
{
public:
	enum class UIScreenState {  //UIScreen�̏��
		EActive  //update()�Einput()���s��
		,EUnControl  //update()�͍s�����Ainput()�͍s��Ȃ�
		,EPause  //update()�Einput()���s��Ȃ�
		,EErace  //�폜����
	};
	enum class UIScreenDrawState {  //UIScreen�̕`����
		EVisible  //�`�悷��
		,EHidden  //�`�悵�Ȃ�(�폜�͂���Ă��Ȃ�)
	};

protected:
	string m_screenName;

	UIScreenState m_UIScreenState;
	UIScreenDrawState m_UIScreenDrawState;

	//vector<unique_ptr<UIActor>> m_UIActorList;
	//queue<unique_ptr<UIActor>> m_UIActorAddQue;

	//UIPanelCanvas* mp_Canvas;

public:
	UIScreen(string _screenName = "");
	virtual ~UIScreen();

	virtual void initialize();
	virtual void update(float _deltaTime);
	virtual void input(float _deltaTime);
	virtual void draw();

	void RemoveAllUIActor();

	//UIPanelCanvas* mp_Canvas;  //���g���������Ă���L�����o�X
	unique_ptr<UIPanelCanvas> mp_Canvas;

public:
	inline string& Name()
	{
		return m_screenName;
	}

	inline const UIScreenState GetUIScreenState()
	{ 
		return m_UIScreenState;
	}
	inline const UIScreenDrawState GetUIScreenDrawState()
	{
		return m_UIScreenDrawState;
	}

	inline void UIScreen::StateActive()
	{
		m_UIScreenState = UIScreenState::EActive;
	}
	inline void UIScreen::StateUnControl()
	{
		m_UIScreenState = UIScreenState::EUnControl;
	}
	inline void UIScreen::StatePause()
	{
		m_UIScreenState = UIScreenState::EPause;
	}
	inline void UIScreen::StateClose()
	{
		m_UIScreenState = UIScreenState::EErace;
	}

	inline void UIScreen::StateVisible()
	{
		m_UIScreenDrawState = UIScreenDrawState::EVisible;
	}
	inline void UIScreen::StateHidden()
	{
		m_UIScreenDrawState = UIScreenDrawState::EHidden;
	}

public:
	/*template <typename T>
	inline T* addUIActor(string _name)
	{
		auto actor = make_unique<T>(_name);
		auto res = actor.get();
		m_UIActorAddQue.push(move(actor));
		res->mp_UIScreenParent = this;
		return res;
	}*/
};


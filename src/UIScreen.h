#pragma once
#include "ofMain.h"
#include "UIActor.h"

/*
* 抽象クラス(継承専用のクラス)
* UIのhierarchyRoot_の様なもの
* これを継承したクラスがUIを配置するキャンパスのようなものになる
*/
class UIScreen
{
public:
	enum class UIScreenState {  //UIScreenの状態
		EActive  //update()・input()を行う
		,EUnControl  //update()は行うが、input()は行わない
		,EPause  //update()・input()を行わない
		,EErace  //削除する
	};
	enum class UIScreenDrawState {  //UIScreenの描画状態
		EVisible  //描画する
		,EHidden  //描画しない(削除はされていない)
	};

protected:
	string m_screenName;

	UIScreenState m_UIScreenState;
	UIScreenDrawState m_UIScreenDrawState;

	vector<unique_ptr<UIActor>> m_UIActorList;
	queue<unique_ptr<UIActor>> m_UIActorAddQue;

public:
	UIScreen(string _name = "");
	virtual ~UIScreen() = 0;

	virtual void update(float _deltaTime) = 0;
	virtual void input(float _deltaTime) = 0;
	virtual void draw(float _deltaTime) = 0;

	void RemoveAllUIActor();

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
	template <typename T>
	inline T* addUIActor()
	{
		auto actor = make_unique<T>();
		auto res = actor.get();
		m_UIActorAddQue.push(move(actor));
		res->mp_UIScreen = this;
		return res;
	}
};


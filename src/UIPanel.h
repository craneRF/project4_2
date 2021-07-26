#pragma once
#include "Actor.h"
#include "UICommon.h"

class UIScreen;

class UIPanel : public Actor
{
protected:
	vector<unique_ptr<UICommon>> m_UICommonChildList;
	queue<unique_ptr<UICommon>> m_UICommonChildAddQue;

	vector<unique_ptr<UIPanel>> m_UIPanelChildList;
	queue<unique_ptr<UIPanel>> m_UIPanelChildAddQue;

public:
	UIPanel(string _name = "");
	virtual ~UIPanel() = 0;

	void caluculateWorldTransform();

	virtual void update(float _deltaTime) = 0;
	virtual void input(float _deltaTime) = 0;
	virtual void draw() = 0;

	void RemoveAllChild();

	UIPanel* mp_UIPanelParent;  //自身がどのUIPanelに存在しているのかを格納する変数
	UIScreen* mp_UIScreenParent;  //自身がどのUIScreenに存在しているのかを格納する変数

public:
	template <typename T>
	inline T* addUICommon(string _name)
	{
		auto uicommon = make_unique<T>(_name);
		uicommon->mp_UIPanelParent = this;
		auto res = uicommon.get();
		m_UICommonChildAddQue.push(move(uicommon));
		return res;
	}

	template <typename T>
	inline T* addUIPanel(string _name)
	{
		auto uipanel = make_unique<T>(_name);
		uipanel->mp_UIPanelParent = this;
		uipanel->mp_UIScreenParent = this->mp_UIScreenParent;
		auto res = uipanel.get();
		m_UPanelChildAddQue.push(move(uipanel));
		return res;
	}
};

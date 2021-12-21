#pragma once
#include "Actor.h"
#include "UICommon.h"

class UIPanelCanvas;

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

	virtual void update() = 0;
	virtual void input() = 0;
	virtual void draw() = 0;

	void RemoveAllChild();

	UIPanel* mp_UIPanelParent;  //���g���ǂ�UIPanel�ɑ��݂��Ă���̂����i�[����ϐ�
	UIPanelCanvas* mp_UICanvasParent;  //���g���ǂ�UIScreen�ɑ��݂��Ă���̂����i�[����ϐ�

	vector<function<void()>> UIupdatefuncVec;
	vector<function<void()>> UIinputfuncVec;
	vector<function<void()>> UIdrawfuncVec;

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
		uipanel->mp_UICanvasParent = this->mp_UICanvasParent;
		auto res = uipanel.get();
		m_UIPanelChildAddQue.push(move(uipanel));
		return res;
	}
};

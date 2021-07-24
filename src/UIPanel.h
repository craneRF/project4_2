#pragma once
#include "UIActor.h"

class UIScreen;

class UIPanel : public UIActor
{
protected:
	vector<unique_ptr<UIActor>> m_UIchildList;
	queue<unique_ptr<UIActor>> m_UIchildAddQue;

public:
	UIPanel(string _name = "");
	virtual ~UIPanel() = 0;

	void caluculateWorldTransform();

	virtual void update(float _deltaTime) = 0;
	virtual void input(float _deltaTime) = 0;
	virtual void draw() = 0;

	void RemoveAllChild();

	UIScreen* mp_UIScreen;  //���g���ǂ�UIScreen�ɑ��݂��Ă���̂����i�[����ϐ��B(UIScreen���폜������UIActor���폜�����)

public:
	template <typename T>
	inline T* addUIChild()
	{
		auto uiactor = make_unique<T>();
		auto res = ui.get();
		m_UIChildAddQue.push(move(ui));
		res->mp_UIparent = this;
		return res;
	}
};

#pragma once
#include "UIActor.h"

class UIPanel : public UIActor
{
protected:
	vector<unique_ptr<UIActor>> m_UIchildList;
	queue<unique_ptr<UIActor>> m_UIchildAddQue;

public:
	UIPanel(string _name = "");
	virtual ~UIPanel() = 0;

	virtual void update(float _deltaTime) = 0;
	virtual void input(float _deltaTime) = 0;
	virtual void draw() = 0;

	void RemoveAllChild();

public:
	template <typename T>
	inline T* addUIChild()
	{
		auto actor = make_unique<T>();
		auto res = actor.get();
		m_UIChildAddQue.push(move(actor));
		res->mp_UIparent = this;
		return res;
	}
};

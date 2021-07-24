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

	UIScreen* mp_UIScreen;  //©g‚ª‚Ç‚ÌUIScreen‚É‘¶İ‚µ‚Ä‚¢‚é‚Ì‚©‚ğŠi”[‚·‚é•Ï”B(UIScreen‚ªíœ‚³‚ê‚é‚ÆUIActor‚àíœ‚³‚ê‚é)

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

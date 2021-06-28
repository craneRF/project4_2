#pragma once
#include "ofMain.h"
#include "Actor.h"
#include "Renderer.h"

/*
* 基本的にコンポーネントを持つことができないGameActorみたいなもの
*/
class UIScreen;

class UIActor : public Actor
{
protected:
	vector<unique_ptr<UIActor>> m_UIchildList;
	queue<unique_ptr<UIActor>> m_UIchildAddQue;

	unique_ptr<FontRenderer> mp_fontRenderer;
	unique_ptr<TextureRenderer> mp_TexRenderer;

public:
	UIActor(string _name = "");
	virtual ~UIActor();

	void caluculateWorldTransform() override;

	void update(float _deltaTime);
	void input(float _deltaTime);
	void draw(float _deltaTime);

	void RemoveAllChild();

	UIActor* mp_UIparent;  
	UIScreen* mp_UIScreen;  //自身がどのUIScreenに存在しているのかを格納する変数。(UIScreenが削除されるとUIActorも削除される)

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


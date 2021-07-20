#pragma once
#include "ofMain.h"
#include "Actor.h"
#include "Renderer.h"

/*
* ���ۃN���X(�p����p�̃N���X)
*
* ��{�I�ɃR���|�[�l���g�������Ƃ��ł��Ȃ�GameActor�݂����Ȃ���
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
	virtual ~UIActor() = 0;

	void caluculateWorldTransform() override;

	virtual void update(float _deltaTime) = 0;
	virtual void input(float _deltaTime) = 0;
	virtual void draw() = 0;

	void RemoveAllChild();

	UIActor* mp_UIparent;  
	UIScreen* mp_UIScreen;  //���g���ǂ�UIScreen�ɑ��݂��Ă���̂����i�[����ϐ��B(UIScreen���폜������UIActor���폜�����)

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


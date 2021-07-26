#pragma once
#include"ofMain.h"
#include "Actor.h"
#include "Component.h"

class GameActor : public Actor
{
protected:
	vector<unique_ptr<Component>> m_componentList;
	vector<unique_ptr<GameActor>> m_childList;
	queue<unique_ptr<GameActor>> m_childAddQue;

public:
	GameActor(string _name = "");
	~GameActor();

	void caluculateWorldTransform();

	void update(float _deltaTime);	//åpè≥ÇµÇ»Ç¢
	void input(float _deltaTime);	//åpè≥ÇµÇ»Ç¢
	void draw();	//åpè≥ÇµÇ»Ç¢

	GameActor* addChild();
	void RemoveAllChild();

	static GameActor* createPlayer(GameActor* _parent, ofVec3f _pos, string _name = "Player");
	static GameActor* createEnemy(GameActor* _parent, ofVec3f _pos, string _name = "Enemy");

	static list<GameActor*>&& findActors(GameActor* _current, string _name, list<GameActor*>&& _list = list<GameActor*>());

	void onCollision(class CollisionComponent* _other);

	GameActor* mp_parent;

	function<void()> drawfunc;

public:
	inline void GameActor::StateAllCpntActive()
	{
		for (auto& cpnt : m_componentList) {
			cpnt->StateCpntActive();
		}
		if (!m_childList.empty()) {
			for (auto& gac : m_childList) {
				for (auto& cpnt : m_componentList) {
					cpnt->StateCpntActive();
				}
			}
		}
	}

	inline void GameActor::StateAllCpntUnControl()
	{
		for (auto& cpnt : m_componentList) {
			cpnt->StateCpntUnControl();
		}
		if (!m_childList.empty()) {
			for (auto& gac : m_childList) {
				for (auto& cpnt : m_componentList) {
					cpnt->StateCpntUnControl();
				}
			}
		}
	}

	inline void GameActor::StateAllCpntPause()
	{
		for (auto& cpnt : m_componentList) {
			cpnt->StateCpntPause();
		}
		if (!m_childList.empty()) {
			for (auto& gac : m_childList) {
				for (auto& cpnt : m_componentList) {
					cpnt->StateCpntPause();
				}
			}
		}
	}

	inline void GameActor::StateAllCpntErace()
	{
		for (auto& cpnt : m_componentList) {
			cpnt->StateCpntErace();
		}
		if (!m_childList.empty()) {
			for (auto& gac : m_childList) {
				for (auto& cpnt : m_componentList) {
					cpnt->StateCpntErace();
				}
			}
		}
	}

	inline void GameActor::StateAllCpntVisible()
	{
		for (auto& cpnt : m_componentList) {
			cpnt->StateCpntVisible();
		}
		if (!m_childList.empty()) {
			for (auto& gac : m_childList) {
				for (auto& cpnt : m_componentList) {
					cpnt->StateCpntVisible();
				}
			}
		}
	}

	inline void GameActor::StateAllCpntHidden()
	{
		for (auto& cpnt : m_componentList) {
			cpnt->StateCpntHidden();
		}
		if (!m_childList.empty()) {
			for (auto& gac : m_childList) {
				for (auto& cpnt : m_componentList) {
					cpnt->StateCpntHidden();
				}
			}
		}
	}

public:
	template <typename T>
	T* addComponent() {
		auto tmp = make_unique<T>(this);
		auto res = tmp.get();
		m_componentList.push_back(move(tmp));
		return res;
	}

	template <typename T>
	T* getComponent() {
		for (auto& cpnt : m_componentList) {
			if (typeid(T) == typeid(*cpnt.get())) {
				return (dynamic_cast<T*>(cpnt.get()));
			}
		}
		return nullptr;
	}
};
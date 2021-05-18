#pragma once
#include"ofMain.h"
#include "Component.h"
#include "stdComponent.h"

class GameActor
{
private:
protected:
	ofVec3f m_pos;
	ofVec3f m_worldPos;

	float m_rotAngle;
	float m_worldRotAngle;

	ofVec3f m_scale;
	ofVec3f m_worldScale;

	vector<unique_ptr<Component>> mp_componentList;
	string m_name;
	vector<unique_ptr<GameActor>> m_childList;
	queue<unique_ptr<GameActor>> m_childAddQue;
public:
	bool waitforErase_ = false;
	GameActor(string _name = "");
	virtual ~GameActor();

	ofVec3f& Pos();
	const ofVec3f& WorldPos();
	float& RotAngle();
	ofVec3f& Scale();

	string& Name();

	void caluculateWorldTransform();
	function<void()> drawfunc;

	void update(float _deltaTime);	//åpè≥ÇµÇ»Ç¢
	void draw(float _deltaTime);	//åpè≥ÇµÇ»Ç¢


	void initialize(ofVec3f _pos, string _name);

	GameActor* m_parent;
	GameActor* addChild();

	void RemoveAllChild();

	static GameActor* createPlayer(GameActor* _parent, ofVec3f _pos, string _name = "Player");
	static void createEnemy(GameActor* _parent, ofVec3f _pos, string _name = "Enemy");

	static list<GameActor*>&& findActors(GameActor* _current, string _name, list<GameActor*>&& _list = list<GameActor*>());

	void onCollision(CollisionComponent* _other);
	template <typename T>
	T* addComponent() {
		auto tmp = make_unique<T>(this);
		auto res = tmp.get();
		mp_componentList.push_back(move(tmp));
		return res;
	}

	template <typename T>
	T* getComponent() {
		for (auto& cpnt : mp_componentList) {
			if (typeid(T) == typeid(*cpnt.get())) {
				return (dynamic_cast<T*>(cpnt.get()));
			}
		}
		return nullptr;
	}
};
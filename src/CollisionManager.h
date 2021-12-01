#pragma once
#include "CollisionObj.h"
enum CollisionType {
	DEFAULT,
	PLAYER_OBJECT,
	PLAYER_BULLET,
	ENEMY_OBJECT,
	ENEMY_BULLET,
};

static const int CollisionTypeMax = CollisionType::ENEMY_BULLET + 1;

class CollisionManager
{
public:
	vector<unique_ptr<CollisionObj> > objpool_;
	//vector<unique_ptr<CollisionComponent>> objpool_;
	CollisionType m_ctype;

	CollisionManager();
	virtual ~CollisionManager();

	CollisionObj* getObj(CollisionComponent* _compo);
	void releaseObj(CollisionObj* _target);
	void CaluculateCollision();
	static bool CollisionMatrix[CollisionTypeMax][CollisionTypeMax];

//public:
//	template <typename T>
//	CollisionComponent* getObj(T* _compo) {
//		cout << typeid(_compo).name() << endl;
//		objpool_.push_back(make_unique<CollisionComponent>(_compo));
//		return objpool_.back().get();
//	}
};


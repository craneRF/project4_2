#include "CollisionObj.h"
#include "CollisionManager.h"
#include "CollisionComponent.h"
#include "GameActor.h"

bool CollisionManager::CollisionMatrix[CollisionTypeMax][CollisionTypeMax] = {
	//DEFAULT POBJECT PBULLET EOBJECT EBULLET
	{false, false, false, false, false}, //DEFAULT
	{false, false, false, true, true}, //PLAYER_OBJECT
	{false, false, false, true, false}, //PLAYER_BULLET
	{false, true, true, false, false}, //ENEMY_OBJECT
	{false, true, false, false, false}, //ENEMY_BULLET
};

CollisionManager::CollisionManager() {
	objpool_.reserve(1000);
}
CollisionManager::~CollisionManager() {
}

CollisionObj* CollisionManager::getObj(CollisionComponent* _compo) {
	objpool_.push_back(make_unique<CollisionObj>(_compo));
	return objpool_.back().get();
}

void CollisionManager::releaseObj(CollisionObj* _target) {
	auto res = find_if(objpool_.begin(), objpool_.end(),
		[&](const auto& c) {return c.get() == _target; });
	assert(res != objpool_.end());
	objpool_.erase(res);
}
void CollisionManager::CaluculateCollision() {
	int poolsize = objpool_.size();
	for (int i = 0; i < poolsize - 1; ++i) {
		for (int j = i + 1; j < poolsize; ++j) {
			if (CollisionMatrix[objpool_[i]->m_ctype][objpool_[j]->m_ctype]) 
			{
				if (objpool_[i]->checkCollide(*objpool_[j])) {
					objpool_[i]->mp_compo->m_onCollisionFunc(objpool_[j]->mp_compo);
					objpool_[j]->mp_compo->m_onCollisionFunc(objpool_[i]->mp_compo);
				}
			}
		}
	}
}
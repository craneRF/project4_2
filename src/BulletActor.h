#pragma once
#include <memory>
#include "GameActor.h"

class BulletActor : public GameActor
{
private:
	static BulletActor* createBullet(GameActor* _parent, ofVec3f _pos, ofVec3f _target, BulletType _bulletType);
public:
	static BulletActor* createPlayerBullet(GameActor* _parent, ofVec3f _pos, ofVec3f _target, BulletType _bulletType);
	static BulletActor* createEnemyBullet(GameActor* _parent, ofVec3f _pos, ofVec3f _target, BulletType _bulletType);
};
#pragma once
#include <memory>
#include "GameActor.h"

class BulletActor : public GameActor
{
private:
	static GameActor* createBullet(GameActor* _parent, ofVec3f _pos, ofVec3f _target, BulletType _bulletType);
public:
	BulletActor(string _name = "");

	static GameActor* createPlayerBullet(GameActor* _parent, ofVec3f _pos, ofVec3f _target, const int _bulletAttack, const int _charaAttack, BulletType _bulletType);
	static GameActor* createEnemyBullet(GameActor* _parent, ofVec3f _pos, ofVec3f _target, const int _bulletAttack, const int _charaAttack, BulletType _bulletType);
};
#pragma once
#include "ofMain.h"
#include "Component.h"
#include "BulletObject.h"

class GameActor;
class CollisionComponent;
class SpriteComponent;
class MoveComponent;

enum class BulletType
{
	Nomal,
	Small,
	//Big,
	TypeNum
};

class BulletComponent  final : public Component
{
private:
	SpriteComponent * mp_sprCpnt;
	MoveComponent * mp_moveCpnt;

	BulletType m_bulletType;
	ofVec3f m_target;

	static BulletObject m_stdBullet;
	static NomalBullet m_nomalBullet;
	static SmallBullet m_smallBullet;
public:
	BulletComponent(GameActor* _gactor);
	virtual ~BulletComponent();

	void initialize(const ofVec3f& _target, const BulletType _bulletType);

	virtual void update(float _deltatime);
	virtual void input(float _deltatime);
	void onCollision(CollisionComponent*);

	BulletType getBulletType() { return m_bulletType; }
	static BulletParam getBullet(BulletType _bulletType);
	const ofVec3f& getTarget() { return m_target; }
};

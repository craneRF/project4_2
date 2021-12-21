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
	Big,
	TypeNum
};

class BulletComponent  final : public Component
{
private:
	SpriteComponent * mp_sprCpnt;
	MoveComponent * mp_moveCpnt;
	CollisionComponent * mp_collisionCpnt;
	// この弾を管理している戦闘コンポーネント
	BattleComponent* mp_battleCpnt;

	// 弾のタイプ
	BulletType m_bulletType;
	// ターゲットの座標
	ofVec3f m_target;
	// 弾の向き
	ofVec3f m_vec;
	// この弾を出したキャラクターの攻撃力
	int m_attack = 1;

	static BulletObject m_stdBullet;
	static NomalBullet m_nomalBullet;
	static SmallBullet m_smallBullet;
	static BoundBullet m_boundBullet;

public:
	BulletComponent(GameActor* _gactor);
	virtual ~BulletComponent();

	void initialize(const ofVec3f& _target, const BulletType _bulletType, const CollisionType _colType, const ofVec3f& _vec = {1,1});

	virtual void update();
	virtual void input();
	void onCollision(CollisionComponent*);

	void SetVec(const ofVec3f& _vec) { m_vec = _vec; }
	void SetBattleComponent(BattleComponent* _battleCpnt) { mp_battleCpnt = _battleCpnt; }

	BulletType getBulletType() { return m_bulletType; }
	static BulletParam getBullet(BulletType _bulletType);
	const ofVec3f& getTarget() { return m_target; }
	const ofVec3f& getVec() { return m_vec; }
	const CollisionComponent* getCollisionComponent() { return mp_collisionCpnt; }
};

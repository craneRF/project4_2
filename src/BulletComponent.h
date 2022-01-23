#pragma once
#include "ofMain.h"
#include "Component.h"
#include "BulletObject.h"

class GameActor;
class CollisionComponent;
class SpriteComponent;
class MoveComponent;

class BulletComponent  final : public Component
{
private:
	SpriteComponent * mp_sprCpnt;
	MoveComponent * mp_moveCpnt;
	CollisionComponent * mp_collisionCpnt;
	// ���̒e���Ǘ����Ă���퓬�R���|�[�l���g
	BattleComponent* mp_battleCpnt;

	// �e�̃^�C�v
	BulletType m_bulletType;
	// �^�[�Q�b�g�̍��W
	ofVec3f m_target;
	// �e�̌���
	ofVec3f m_vec;
	// ���̒e���o�����L�����N�^�[�̍U����
	int m_attack = 1;
	// ���������ォ
	bool m_isHit = false;
	string m_needKey;

	static unordered_map<BulletType, unique_ptr<BulletObject>> m_bulletMap;

public:
	BulletComponent(GameActor* _gactor);
	virtual ~BulletComponent();

	void initialize(const ofVec3f& _target, const BulletType _bulletType, const CollisionType _colType, const int _attack, const ofVec3f& _vec = {1,1});

	virtual void update();
	virtual void input();
	void onCollision(CollisionComponent*);

	void Destroy();
	void SetVec(const ofVec3f& _vec) { m_vec = _vec; }
	void SetBattleComponent(BattleComponent* _battleCpnt) { mp_battleCpnt = _battleCpnt; }
	void SetNeedKey(string& _needKey) { m_needKey = _needKey; }

	string GetNeedKey() { return m_needKey; }
	BulletType getBulletType() { return m_bulletType; }
	static BulletParam getBullet(BulletType _bulletType);
	static void InitBulletMap();
	const ofVec3f& getTarget() { return m_target; }
	const ofVec3f& getVec() { return m_vec; }
	const CollisionComponent* getCollisionComponent() { return mp_collisionCpnt; }
	const MoveComponent* getMoveComponent() { return mp_moveCpnt; }
};

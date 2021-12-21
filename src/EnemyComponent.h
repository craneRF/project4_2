#pragma once
#include "ofMain.h"
#include "Component.h"
#include "EnemyObject.h"

class GameActor;
class BattleComponent;

enum EnemyType;
struct EnemyParam;
struct EnemyParts;

class EnemyComponent  final : public Component
{
	friend class NomalEnemy;
private:
	// ���̓G������퓬�R���|�[�l���g
	BattleComponent* mp_battleCpnt;
	// �G�̃^�C�v
	int m_EnemyType = 0;

	static EnemyObject m_stdEnemy;
	static NomalEnemy m_nomalEnemy;
	static SmallEnemy m_smallEnemy;
public:
	EnemyComponent(GameActor* _gactor);
	virtual ~EnemyComponent();

	void Initialize(BattleComponent* _battleCpnt, const int _enemytype);

	virtual void update();
	virtual void input();
	// ���S���ɌĂяo���֐�
	void onDestroy();

	void AddCommand(const string _fromName, const string _toName, const int _commandType, const int _commandval);
	EnemyParam getEnemy(int _enemytype);
	void setEnemyType(int _enemytype) { m_EnemyType = _enemytype; }
};

class EnemyPartsComponent : public Component
{
protected:
	// ���̕��ʂ����G�R���|�[�l���g
	EnemyComponent* mp_enemyCpnt;
	// �̗�
	int m_hp = 10;
	// �h���
	int m_def = 0;
	// ���̂ȂǏd�v�ȕ��ʂ�
	bool m_isCore = true;

public:
	EnemyPartsComponent(GameActor* _gactor);
	virtual ~EnemyPartsComponent();

	void Initialize(const EnemyParts& _enemyParts, EnemyComponent* _enemyCpnt);

	virtual void update();
	virtual void input();
	void onCollision(CollisionComponent*);
	// �_���[�W�����i�_���[�W�j
	void onDamage(const string& _fromName, const int _damage);
	// �_���[�W�����i�L�����N�^�[�̍U���́A�e�̍U���́j
	void onDamage(const string& _fromName, const int _charaAttack, const int _bulletAttack);
};
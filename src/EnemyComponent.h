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
	// �p�[�c�z��
	vector<class EnemyPartsComponent*> m_partsCpntList;
	// ���̓G������퓬�R���|�[�l���g
	BattleComponent* mp_battleCpnt;
	// �G�̃^�C�v
	EnemyType m_EnemyType;
	bool m_isSelect;

	static EnemyObject m_stdEnemy;
	static unordered_map<EnemyType, EnemyObject> m_enemyMap;

public:
	EnemyComponent(GameActor* _gactor);
	virtual ~EnemyComponent();

	void Initialize(BattleComponent* _battleCpnt, const EnemyType _enemytype);

	virtual void update();
	virtual void input();
	// ���S���ɌĂяo���֐�
	void onDestroy();
	// �X�L���I��
	const EnemySkill SelectSkill();

	void AddParts(class EnemyPartsComponent* _partsCpnt) { m_partsCpntList.emplace_back(_partsCpnt); }
	void DeleteParts(class EnemyPartsComponent* _partsCpnt);
	const vector<class EnemyPartsComponent*>& GetPartsCpntList()const { return m_partsCpntList; }
	void AddCommand(const string _fromName, const string _toName, const int _commandType, const int _commandval);
	const EnemyParam& getEnemy() const;
	EnemyParam getEnemy(EnemyType _enemytype);
	void setEnemyType(EnemyType _enemytype) { m_EnemyType = _enemytype; }
	void SetColor(const ofColor _color);
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
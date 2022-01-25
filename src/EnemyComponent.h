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
	// パーツ配列
	vector<class EnemyPartsComponent*> m_partsCpntList;
	// この敵がいる戦闘コンポーネント
	BattleComponent* mp_battleCpnt;
	// 敵のタイプ
	EnemyType m_EnemyType;
	bool m_isSelect;
	bool m_isAlive = true;
	static EnemyObject m_stdEnemy;
	static unordered_map<EnemyType, EnemyObject> m_enemyMap;

public:
	EnemyComponent(GameActor* _gactor);
	virtual ~EnemyComponent();

	void Initialize(BattleComponent* _battleCpnt, const EnemyType _enemytype);

	virtual void update();
	virtual void input();
	// 死亡時に呼び出す関数
	void onDestroy();
	// スキル選択
	const Skill SelectSkill();
	void CheckIsAlive();

	void AddParts(class EnemyPartsComponent* _partsCpnt) { m_partsCpntList.emplace_back(_partsCpnt); }
	void DeleteParts(class EnemyPartsComponent* _partsCpnt);
	const vector<class EnemyPartsComponent*>& GetPartsCpntList()const { return m_partsCpntList; }
	BattleComponent* GetBattleCpnt() { return mp_battleCpnt; }
	const EnemyParam& getEnemy() const;
	bool GetIsAlive() { return m_isAlive; }
	EnemyParam getEnemy(EnemyType _enemytype);
	void setEnemyType(EnemyType _enemytype) { m_EnemyType = _enemytype; }
	void SetColor(const ofColor _color);
};

class EnemyPartsComponent : public Component
{
protected:
	// この部位を持つ敵コンポーネント
	EnemyComponent* mp_enemyCpnt;
	// 体力
	int m_hp = 10;
	// 防御力
	int m_def = 0;
	// 胴体など重要な部位か
	bool m_isCore = true;
	bool m_isAlive = true;

public:
	EnemyPartsComponent(GameActor* _gactor);
	virtual ~EnemyPartsComponent();

	void Initialize(const EnemyParts& _enemyParts, EnemyComponent* _enemyCpnt);

	virtual void update();
	virtual void input();
	void onCollision(CollisionComponent*);

	void CheckIsAlive();
	// ダメージ処理（ダメージ）
	bool onDamage(const string& _fromName, const int _damage);
	// ダメージ処理（キャラクターの攻撃力、弾の攻撃力）
	bool onDamage(const string& _fromName, const int _charaAttack, const int _bulletAttack);
	bool GetIsAlive()const { return m_isAlive; }
};
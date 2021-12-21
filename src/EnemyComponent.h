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
	// この敵がいる戦闘コンポーネント
	BattleComponent* mp_battleCpnt;
	// 敵のタイプ
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
	// 死亡時に呼び出す関数
	void onDestroy();

	void AddCommand(const string _fromName, const string _toName, const int _commandType, const int _commandval);
	EnemyParam getEnemy(int _enemytype);
	void setEnemyType(int _enemytype) { m_EnemyType = _enemytype; }
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

public:
	EnemyPartsComponent(GameActor* _gactor);
	virtual ~EnemyPartsComponent();

	void Initialize(const EnemyParts& _enemyParts, EnemyComponent* _enemyCpnt);

	virtual void update();
	virtual void input();
	void onCollision(CollisionComponent*);
	// ダメージ処理（ダメージ）
	void onDamage(const string& _fromName, const int _damage);
	// ダメージ処理（キャラクターの攻撃力、弾の攻撃力）
	void onDamage(const string& _fromName, const int _charaAttack, const int _bulletAttack);
};
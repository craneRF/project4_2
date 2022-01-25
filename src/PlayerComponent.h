#pragma once
#include "Component.h"

class GameActor;
class CollisionComponent;
class SpriteComponent;
class BattleComponent;

class PlayerComponent :public Component
{
private:
	// このプレイヤーがいる戦闘コンポーネント
	BattleComponent* mp_battleCpnt;

	ofVec3f m_imageSize;

public:
	PlayerComponent(GameActor *_gactor);
	virtual ~PlayerComponent();

	void Initialize(BattleComponent* _battleCpnt);
	virtual void update();
	virtual void input();
	void onCollision(CollisionComponent*);

	void AddCommand(const string& _fromName, const int _commandType, const int _commandval);

	ofVec3f GetImageSize() const { return m_imageSize; }
};

class PlayerPartsComponent : public Component
{
protected:
	// この部位を持つプレイヤーコンポーネント
	PlayerComponent* mp_playerCpnt;
	// ダメージ倍率
	int m_damageMultiplier = 1;
	// 本体か（本体の場合ガードボタンを押していなくても、ダメージ処理を行う）
	bool m_isCore = true;

public:
	PlayerPartsComponent(GameActor* _gactor);
	virtual ~PlayerPartsComponent();

	void Initialize(const bool _isCore, const int _damageMultiplier, PlayerComponent* _playerCpnt);

	virtual void update();
	virtual void input();
	void onCollision(CollisionComponent* _other);
	// ダメージ処理（ダメージ）
	void onDamage(const string& _fromName, const int _damage);
	// ダメージ処理（キャラクターの攻撃力、弾の攻撃力）
	void onDamage(const string& _fromName, const int _charaAttack, const int _bulletAttack);

	const bool GetIsCore() const { return m_isCore; }
};
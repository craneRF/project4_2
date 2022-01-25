#pragma once
#include "Component.h"

class GameActor;
class CollisionComponent;
class SpriteComponent;
class BattleComponent;

class PlayerComponent :public Component
{
private:
	// ���̃v���C���[������퓬�R���|�[�l���g
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
	// ���̕��ʂ����v���C���[�R���|�[�l���g
	PlayerComponent* mp_playerCpnt;
	// �_���[�W�{��
	int m_damageMultiplier = 1;
	// �{�̂��i�{�̂̏ꍇ�K�[�h�{�^���������Ă��Ȃ��Ă��A�_���[�W�������s���j
	bool m_isCore = true;

public:
	PlayerPartsComponent(GameActor* _gactor);
	virtual ~PlayerPartsComponent();

	void Initialize(const bool _isCore, const int _damageMultiplier, PlayerComponent* _playerCpnt);

	virtual void update();
	virtual void input();
	void onCollision(CollisionComponent* _other);
	// �_���[�W�����i�_���[�W�j
	void onDamage(const string& _fromName, const int _damage);
	// �_���[�W�����i�L�����N�^�[�̍U���́A�e�̍U���́j
	void onDamage(const string& _fromName, const int _charaAttack, const int _bulletAttack);

	const bool GetIsCore() const { return m_isCore; }
};
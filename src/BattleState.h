#pragma once
#include "ofMain.h"

class GameActor;
class Parameter;
class BattleComponent;
enum class Result;
enum class BulletType;
class BattleState
{
private:

protected:
	static queue<int> m_attackQueue;
	string stateName = "";
public:
	static Result result;

	BattleState() {};
	virtual ~BattleState() {};
	virtual void enter(BattleComponent* _battleComponent) = 0;
	virtual BattleState* update(BattleComponent* _battleComponent) = 0;
	virtual void exit(BattleComponent* _battleComponent) = 0;
};

// ������
class InitBattleState final : public BattleState {
private:

public:
	virtual void enter(BattleComponent* _battleComponent);
	virtual BattleState* update(BattleComponent* _battleComponent);
	virtual void exit(BattleComponent* _battleComponent);
};

// �R�}���h�I��
class SelectCommandState final : public BattleState {
private:
	int m_bulletTypeIndex = 0;
public:
	virtual void enter(BattleComponent* _battleComponent);
	virtual BattleState* update(BattleComponent* _battleComponent);
	virtual void exit(BattleComponent* _battleComponent);
};

// ���s����
class JudgeState final : public BattleState {
private:

public:
	virtual void enter(BattleComponent* _battleComponent);
	virtual BattleState* update(BattleComponent* _battleComponent);
	virtual void exit(BattleComponent* _battleComponent);
};

// �K�[�h����
class GuardJudgeState final : public BattleState {
private:

public:
	virtual void enter(BattleComponent* _battleComponent);
	virtual BattleState* update(BattleComponent* _battleComponent);
	virtual void exit(BattleComponent* _battleComponent);
};

// �^�[�����f
class TurnState final : public BattleState {
private:
	int m_turnIndex;
public:
	virtual void enter(BattleComponent* _battleComponent);
	virtual BattleState* update(BattleComponent* _battleComponent);
	virtual void exit(BattleComponent* _battleComponent);
};

// �U���A�N�^�[�쐬
class AttackState final : public BattleState {
private:
	int m_turnCharaIndex;
	int m_targetCharaIndex;
	BulletType m_bulletType;

public:
	virtual void enter(BattleComponent* _battleComponent);
	virtual BattleState* update(BattleComponent* _battleComponent);
	virtual void exit(BattleComponent* _battleComponent);

	void initialize(const int _turnCharaIndex, const int _targetCharaIndex, const BulletType _bulletType)
	{
		m_turnCharaIndex = _turnCharaIndex;
		m_targetCharaIndex = _targetCharaIndex;
		m_bulletType = _bulletType;
	}
};

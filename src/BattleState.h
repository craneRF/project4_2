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
	enum class CommandType
	{
		SKILL,
		ITEM,
		TYPE_NUM,
	};

	struct CommandInfo
	{
		int commandTypeIndex = 0;
		int bulletTypeIndex = 0;
		int fromIndex = 0;
		int targetIndex = 0;
		int partsIndex = 0;
	};

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
	CommandInfo m_commandInfo;
	bool m_isSelectCommandType = false;
	bool m_isSelectBulletType = false;
	bool m_isSelectTarget = false;
	bool m_isSelectParts = false;

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
	GameActor* m_turnChara;
public:
	virtual void enter(BattleComponent* _battleComponent);
	virtual BattleState* update(BattleComponent* _battleComponent);
	virtual void exit(BattleComponent* _battleComponent);
};

// �U���A�N�^�[�쐬
class AttackState final : public BattleState {
private:
	ofVec3f m_fromPos;
	ofVec3f m_targetPos;
	BulletType m_bulletType;
	int m_bulletCount = 1;
	int m_attack = 1;
	bool m_isPlayer = true;

public:
	virtual void enter(BattleComponent* _battleComponent);
	virtual BattleState* update(BattleComponent* _battleComponent);
	virtual void exit(BattleComponent* _battleComponent);

	void initialize(const ofVec3f _fromPos, const ofVec3f _targetPos, const BulletType _bulletType, const int _bulletCount, const int _attack, bool _isPlayer)
	{
		m_fromPos = _fromPos;
		m_targetPos = _targetPos;
		m_bulletType = _bulletType;
		m_bulletCount = _bulletCount;
		m_attack = _attack;
		m_isPlayer = _isPlayer;
	}
};

// �s�k��̑I��
class LoseState final : public BattleState {
private:

public:
	virtual void enter(BattleComponent* _battleComponent);
	virtual BattleState* update(BattleComponent* _battleComponent);
	virtual void exit(BattleComponent* _battleComponent);

};

#pragma once
#include "Component.h"
#include "EnemyActor.h"


class Parameter;
class BattleComponent :public Component
{
public:
	enum class Result
	{
		NONE,
		WIN,
		LOSE,
	};

	struct Command
	{
		int fromIndex;
		int toIdenx;
		int commandType;
		int commandval;
		//void setParam(int _fromIndex, int _toIdenx, int _commandType, int _commandval)
		//{
		//}
	};
private:
	// �Ƃ肠�����̘A�ő΍�
	bool m_IsStart = false;

	// ����
	Result m_result = Result::NONE;

	// �퓬�L����
	shared_ptr<Parameter> m_Player;
	vector<EnemyActor*> m_EnemyList;
	map<string, EnemyActor*>m_EnemyMap;

	// ��HP(���ۂ͐퓬�L�����������Ă���HP���g��)
	//int m_PlayerHP = 10;
	int m_EnemyHP =10;

	string m_Enemyname;

	// ����m�F������
	string m_stateInfo = "";
	// ���݂̍s���L����
	int m_currentChara = 0;
	unique_ptr<Command> mp_Command;

public:

	BattleComponent(GameActor* _gator);
	virtual ~BattleComponent();
	virtual void update(float _deltatime);

	void SetPlayer(shared_ptr<Parameter> _player) { m_Player = _player; }
	void SetEnemy(vector<EnemyActor*> _enemyList);
	Result GetResult() { return m_result; }
	string GetInfo() { return m_stateInfo; }

private:
	// ���s�̃`�F�b�N
	void CheckResult();
	void ExcuteCommand();
};
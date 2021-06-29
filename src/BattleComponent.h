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
	// とりあえずの連打対策
	bool m_IsStart = false;

	// 結果
	Result m_result = Result::NONE;

	// 戦闘キャラ
	shared_ptr<Parameter> m_Player;
	vector<EnemyActor*> m_EnemyList;
	map<string, EnemyActor*>m_EnemyMap;

	// 仮HP(実際は戦闘キャラが持っているHPを使う)
	//int m_PlayerHP = 10;
	int m_EnemyHP =10;

	string m_Enemyname;

	// 動作確認文字列
	string m_stateInfo = "";
	// 現在の行動キャラ
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
	// 勝敗のチェック
	void CheckResult();
	void ExcuteCommand();
};
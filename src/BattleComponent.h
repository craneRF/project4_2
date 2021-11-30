#pragma once
#include "Component.h"
#include "EnemyActor.h"
#include "PlayerActor.h"

struct Command
{
	int fromIndex;
	int toIndex;
	int commandType;
	int commandval;
};
enum class Result
{
	NONE,
	WIN,
	LOSE,
};

class Parameter;
class BattleState;
class BattleComponent :public Component
{
private:
	unique_ptr<BattleState> mp_battleState;
	unique_ptr<Command> mp_Command;

	// 戦闘キャラ
	PlayerActor *mp_charaActor;
	shared_ptr<Parameter> mp_Player;
	// 敵リスト
	vector<EnemyActor*> m_EnemyList;
	// map<string, EnemyActor*>m_EnemyMap;

	list<GameActor*> m_bulletList;

	int m_EnemyHP = 0;

	string m_Enemyname;

	// 動作確認文字列
	string m_stateInfo = "";

public:
	BattleComponent(GameActor* _gator);
	virtual ~BattleComponent();
	virtual void update(float _deltatime);
	virtual void input(float _deltatime);

	void SetPlayer(shared_ptr<Parameter> _player) { mp_Player = _player; }
	void SetCommand(Command* _command) { mp_Command.reset(_command); }

	void AddBullet(GameActor* _bulletActor) { m_bulletList.emplace_back(_bulletActor); }

	const ofVec3f& GetPlayerPos() { return mp_charaActor->Pos(); }
	const ofVec3f& GetEnemyPos(const int _index) { return m_EnemyList.at(_index)->Pos(); }
	shared_ptr<Parameter> GetPlayer() { return mp_Player; }
	const int GetEnemyHp() const { return m_EnemyHP; }
	Result GetResult();
	const string& GetInfo() const { return m_stateInfo; }
	const int GetBulletCount() const { return m_bulletList.size(); }
private:
	void ExcuteCommand();
	// 敵リストの初期化
	void InitEnemyList();

};
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

	Command(const int _fromIndex,const int _toIndex,const int _commandType,const int _commandval) :
		fromIndex(_fromIndex),
		toIndex(_toIndex),
		commandType(_commandType),
		commandval(_commandval)
	{}
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
	queue<unique_ptr<Command>> m_commandList;

	// �퓬�L����
	PlayerActor *mp_charaActor;
	shared_ptr<Parameter> mp_Player;
	// �G���X�g
	vector<EnemyActor*> m_EnemyList;
	// map<string, EnemyActor*>m_EnemyMap;

	list<GameActor*> m_bulletList;

	int m_EnemyHP = 0;

	string m_Enemyname;

	// ����m�F������
	string m_stateInfo = "";

public:
	BattleComponent(GameActor* _gator);
	virtual ~BattleComponent();
	virtual void update();
	virtual void input();

	void SetPlayer(shared_ptr<Parameter> _player) { mp_Player = _player; }

	// �e��ǉ�
	void AddBullet(GameActor* _bulletActor) {m_bulletList.emplace_back(_bulletActor);};
	// �e���폜
	void DeleteBullet(GameActor* _bulletActor) {
		auto res = find_if(m_bulletList.begin(), m_bulletList.end(),
			[&](const auto& c) {return c == _bulletActor; });
		assert(res != m_bulletList.end());
		m_bulletList.erase(res);
	}

	const ofVec3f& GetPlayerPos() { return mp_charaActor->Pos(); }
	const ofVec3f& GetEnemyPos(const int _index) { return m_EnemyList.at(_index)->Pos(); }
	shared_ptr<Parameter> GetPlayer() { return mp_Player; }
	const int GetEnemyHp() const { return m_EnemyHP; }
	Result GetResult();
	const string& GetInfo() const { return m_stateInfo; }
	const int GetBulletCount() const { return m_bulletList.size(); }
private:
	void ExcuteCommand();
	// �G���X�g�̏�����
	void InitEnemyList();

};
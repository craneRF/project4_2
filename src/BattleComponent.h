#pragma once
#include "Component.h"
#include "EnemyActor.h"
#include "PlayerActor.h"

struct Command
{
	string fromName;
	string toName;
	int commandType;
	int commandval;

	Command(const string _fromName, const string _toName, const int _commandType, const int _commandval) :
		fromName(_fromName),
		toName(_toName),
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
	vector<GameActor*> m_EnemyList;
	// �e���X�g
	vector<GameActor*> m_bulletList;

	// ����m�F������
	string m_stateInfo = "";

public:
	BattleComponent(GameActor* _gator);
	virtual ~BattleComponent();
	virtual void update();
	virtual void input();

	void SetPlayer(shared_ptr<Parameter> _player) { mp_Player = _player; }

	// �e��ǉ�
	void AddBullet(GameActor* _bulletActor);
	// �e���폜
	void DeleteBullet(GameActor* _bulletActor);

	// �e���X�g���擾
	const std::vector <GameActor*>& GetBulletList() const { return m_bulletList; }

	// �R�}���h��ǉ�
	void AddCommand(unique_ptr<Command>&& _command);

	// �G���폜
	void DeleteEnemy(GameActor* _actor);

	const ofVec3f& GetPlayerPos() { return mp_charaActor->Pos(); }
	GameActor* GetEnemy(const int _index) { return m_EnemyList.at(_index); }
	const int GetEnemyCount() const { return m_EnemyList.size(); }
	shared_ptr<Parameter> GetPlayer() { return mp_Player; }
	Result GetResult();
	const string GetInfo() const { return m_stateInfo; }
	const int GetBulletCount() const { return m_bulletList.size(); }
	//const int GetBulletCount() const { return m_bulletList.size(); }
private:
	void ExcuteCommand();
	// �G���X�g�̏�����
	void InitEnemyList();

};
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
	LOSE_CONTINUE,
	LOSE_OVER,
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
	// �G���X�g
	vector<GameActor*> m_EnemyList;
	// �e���X�g
	vector<GameActor*> m_bulletList;
	// �U����
	list<GameActor*> m_attackList;

	// ����m�F������
	string m_stateInfo = "";
	// ���b�Z�[�W�z��
	queue<string> m_messageList;
	// �{�X�킩�ǂ���
	bool m_isBossBattle = false;
public:
	BattleComponent(GameActor* _gator);
	virtual ~BattleComponent();
	virtual void update();
	virtual void input();

	// ������
	void Initialize(const bool _isBossBattle);
	// �e��ǉ�
	void AddBullet(GameActor* _bulletActor);
	// �e���폜
	void DeleteBullet(GameActor* _bulletActor);

	// �e���X�g���擾
	const std::vector <GameActor*>& GetBulletList() const { return m_bulletList; }

	// �R�}���h��ǉ�
	void AddCommand(unique_ptr<Command>&& _command);
	// ���b�Z�[�W��ǉ�
	void AddMessage(string& _message) { m_messageList.emplace(_message); }
	// ���b�Z�[�W���㏑��
	void SetMessage(string& _message) { m_stateInfo = _message; }
	// �G���폜
	void DeleteEnemy(GameActor* _actor);

	// �s�����ݒ�
	void InitAttackOrder();
	// ���ɍs������L�����̃A�N�^�[���擾
	GameActor* GetNextAttackChara() {
		auto res = m_attackList.front();
		m_attackList.pop_front();
		return res; 
	}

	GameActor* GetPlayer() { return mp_charaActor; }
	GameActor* GetEnemy(const int _index) { return m_EnemyList.at(_index); }
	const int GetEnemyCount() const { return m_EnemyList.size(); }
	Result GetResult();
	const string& GetInfo() const { return m_stateInfo; }
	const int GetBulletCount() const { return m_bulletList.size(); }

private:
	void ExcuteCommand();
	// �G���X�g�̏�����
	void InitEnemyList();
};
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

	// 戦闘キャラ
	PlayerActor *mp_charaActor;
	shared_ptr<Parameter> mp_Player;
	// 敵リスト
	vector<GameActor*> m_EnemyList;
	// 弾リスト
	vector<GameActor*> m_bulletList;

	// 動作確認文字列
	string m_stateInfo = "";

public:
	BattleComponent(GameActor* _gator);
	virtual ~BattleComponent();
	virtual void update();
	virtual void input();

	void SetPlayer(shared_ptr<Parameter> _player) { mp_Player = _player; }

	// 弾を追加
	void AddBullet(GameActor* _bulletActor);
	// 弾を削除
	void DeleteBullet(GameActor* _bulletActor);

	// 弾リストを取得
	const std::vector <GameActor*>& GetBulletList() const { return m_bulletList; }

	// コマンドを追加
	void AddCommand(unique_ptr<Command>&& _command);

	// 敵を削除
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
	// 敵リストの初期化
	void InitEnemyList();

};
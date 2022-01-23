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

	// 戦闘キャラ
	PlayerActor *mp_charaActor;
	// 敵リスト
	vector<GameActor*> m_EnemyList;
	// 弾リスト
	vector<GameActor*> m_bulletList;
	// 攻撃順
	list<GameActor*> m_attackList;

	// 動作確認文字列
	string m_stateInfo = "";
	// メッセージ配列
	queue<string> m_messageList;
	// ボス戦かどうか
	bool m_isBossBattle = false;
public:
	BattleComponent(GameActor* _gator);
	virtual ~BattleComponent();
	virtual void update();
	virtual void input();

	// 初期化
	void Initialize(const bool _isBossBattle);
	// 弾を追加
	void AddBullet(GameActor* _bulletActor);
	// 弾を削除
	void DeleteBullet(GameActor* _bulletActor);

	// 弾リストを取得
	const std::vector <GameActor*>& GetBulletList() const { return m_bulletList; }

	// コマンドを追加
	void AddCommand(unique_ptr<Command>&& _command);
	// メッセージを追加
	void AddMessage(string& _message) { m_messageList.emplace(_message); }
	// メッセージを上書き
	void SetMessage(string& _message) { m_stateInfo = _message; }
	// 敵を削除
	void DeleteEnemy(GameActor* _actor);

	// 行動順設定
	void InitAttackOrder();
	// 次に行動するキャラのアクターを取得
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
	// 敵リストの初期化
	void InitEnemyList();
};
#pragma once
#include "ofMain.h"
#include "PlayerActor.h"
#include "EnemyActor.h"

class Parameter;
class GameState
{
private:

protected:
	GameActor* mp_fontActor;
	GameActor* mp_operationFontactor;	// 操作方法を表示するアクター
	GameActor* mp_actor1;
	GameActor* mp_actor2;
	GameActor* mp_itemlist;

public:
	GameState() {};
	virtual ~GameState() {};
	virtual void enter() = 0;
	virtual GameState* update() = 0;
	virtual void exit() = 0;
};

// タイトルシーン
class GameStateTitle final : public GameState {
private:
	ofPath path;

public:
	virtual void enter();
	virtual GameState* update();
	virtual void exit();

	class GameActor* mp_rect;
	class GameActor* mp_rect2;
	class GameActor* mp_marin;
};

// ゲームクリアシーン
class GameStateClear final : public GameState {
private:

public:
	virtual void enter();
	virtual GameState* update();
	virtual void exit();
};

// ゲームオーバーシーン
class GameStateOver final : public GameState {
private:
	vector<class FontRendererComponent*> m_selectFontCpntList;
	vector<function<GameState*()>> m_funcList;
	int m_selectIndex = 0;

public:
	virtual void enter();
	virtual GameState* update();
	virtual void exit();
};

class MapComponent;
// マップシーン
class GameStateMap final : public GameState {
private:
	MapComponent* mp_mapComp;

public:
	virtual void enter();
	virtual GameState* update();
	virtual void exit();
};

class BattleComponent;
// 戦闘シーン
class GameStateBattle final : public GameState {
private:
	// 戦闘システム
	BattleComponent* mp_BattleComp;
	GameActor* mp_hpFontActor;
	// 戦闘前のパラメータ
	unique_ptr<Parameter> mp_prePrameter;
	// ボス戦か
	bool m_isBossBattle = false;

public:
	virtual void enter();
	virtual GameState* update();
	virtual void exit();

	void SetIsBossBattle(const bool _isBossBattle) { m_isBossBattle = _isBossBattle; }
};

// イベントシーン
class GameStateEvent final : public GameState {
private:
	enum class EVENT_INDEX
	{
		NONE,
		HEAL,
		DAMAGE,
		ATTACK_UP,
		INDEX_NUM,
	};
	// イベント前のパラメータ
	unique_ptr<Parameter> mp_prePrameter;

	bool m_isDead = false;

public:
	virtual void enter();
	virtual GameState* update();
	virtual void exit();
};
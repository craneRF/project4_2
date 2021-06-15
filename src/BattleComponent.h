#pragma once
#include "Component.h"

class BattleComponent :public Component
{
public:
	enum class Result
	{
		NONE,
		WIN,
		LOSE,
	};
	enum class Turn
	{
		NONE,
		ME,
		ENEMY,
	};

private:
	int m_selectIndex = 0;
	// とりあえずの連打対策
	bool m_start = false;

	// 結果
	Result m_result = Result::NONE;
	// ターン
	Turn m_turn = Turn::NONE;

public:
	BattleComponent(GameActor* _gator);
	virtual ~BattleComponent();
	virtual void update(float _deltatime);

	Result GetResult() { return m_result; }
private:
	// 勝敗のチェック
	void CheckResult();
};
#pragma once
#include "Component.h"

// マスの種類
enum class StepKind
{
	EVENT,			// イベント
	BATTLE,			// 戦闘
	MAXNUM,			// 道中イベントの種類数（↑の数）
	START,			// スタート
	GOAL,			// ゴール
	NONE,			// 未設定
};

// マス
struct Step
{
	int m_id = 0;					// マスID
	ofVec3f m_pos;					// マス座標
	bool m_IsSelected = false;		// 選択フラグ
	bool m_IsFocused = false;		// フォーカスフラグ
	StepKind m_kind;				// マスの種類
	vector<Step*> m_nextStepList;	// 次進むことができるマスのリスト
};

class MapState;
class MapComponent :public Component
{
	friend class InitMapState;
	friend class SelectMapState;

private:
	// マップの構造
	static vector<vector<unique_ptr<Step>>> m_Map;
	// 現在止まっているマスのポインタ
	static Step* mp_currentStep;
	unique_ptr<MapState> mp_mapState;
	StepKind m_stepKind;

public:
	MapComponent(GameActor* _gator);
	virtual ~MapComponent();
	virtual void update();
	virtual void input();

	void Initialize();
	void SetResKind(StepKind _stepKind) { m_stepKind = _stepKind; }
	StepKind GetResKind() { return m_stepKind; }
	static void ClearMap();

};
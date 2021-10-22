#pragma once
#include "ofMain.h"

class GameActor;
class Parameter;
class MapComponent;

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
	StepKind m_kind;				// マスの種類
	vector<Step*> m_nextStepList;	// 次進むことができるマスのリスト
};

class MapState
{
private:

protected:
	static int m_selectIndex;

public:
	// マップの構造
	static vector<vector<unique_ptr<Step>>> m_Map;
	// 現在止まっているマスのポインタ
	static Step* mp_currentStep;

	MapState() {};
	virtual ~MapState() {};
	virtual void enter(MapComponent* _mapComponent) = 0;
	virtual MapState* update(MapComponent* _mapComponent) = 0;
	virtual void exit(MapComponent* _mapComponent) = 0;

	void ClearMap();
};

// 初期化
class InitMapState final : public MapState {
private:
	// マス同士をつなげる確率(%)
	const int m_ConnectPercent = 100;

	void Initialize(GameActor* _mapActor);
	// マップのランダム生成
	void CreateRandomMap();
	void CreateStepActor(GameActor* _mapActor);
	void DrawLine(Step* _step);

public:

	virtual void enter(MapComponent* _mapComponent);
	virtual MapState* update(MapComponent* _mapComponent);
	virtual void exit(MapComponent* _mapComponent);
};

// マス選択
class SelectMapState final : public MapState {
private:

public:
	virtual void enter(MapComponent* _mapComponent);
	virtual MapState* update(MapComponent* _mapComponent);
	virtual void exit(MapComponent* _mapComponent);
};

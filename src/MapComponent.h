#pragma once
#include "Component.h"

class MapComponent :public Component
{
public:
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

private:
	int m_selectIndex = 0;
	// とりあえずの連打対策
	bool m_start = false;
	StepKind m_resKind = StepKind::NONE;
	// マップの構造
	static vector<vector<unique_ptr<Step>>> m_Map;

	// 現在止まっているマスのポインタ
	static Step* mp_currentStep;

	// マス同士をつなげる確率(%)
	const int m_ConnectPercent = 100;

	UINT timeCount = 0;
public:
	MapComponent(GameActor* _gator);
	virtual ~MapComponent();
	virtual void update();
	virtual void input();

	// CSVファイルからマップ情報読み込み
	void LoadMap(string _filePath);
	// マップのランダム生成
	void CreateRandomMap();
	void CreateRandomMap2();
	void CreateStepActor();
	StepKind GetResKind() { return m_resKind; }
	void ClearMap();

private:
	void DrawLine(Step* _step);

};
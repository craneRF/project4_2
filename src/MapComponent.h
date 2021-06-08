#pragma once
#include "Component.h"

class MapComponent :public Component
{
public:
	enum class StepKind
	{
		NONE,
		START,
		EVENT,
		BATTLE,
		GOAL,
	};

private:
	struct Step
	{
		int m_index;
		ofVec3f m_pos;
		bool m_IsSelected;
		StepKind m_kind;
		vector<int> m_nextIndex;
	};

	int m_selectIndex = 0;
	// とりあえずの連打対策
	bool m_start = false;
	StepKind m_resKind = StepKind::NONE;
	vector<unique_ptr<Step>> m_Map;
	// 通ってきたマスのインデックスを保管しておくコンテナ
	stack<int> m_path;

public:
	MapComponent(GameActor* _gator);
	virtual ~MapComponent();
	virtual void update(float _deltatime);

	void LoadMap(string _filePath);
	StepKind GetResKind() { return m_resKind; }
private:
	// 引数のマスとつながっているマスを線でつなげる
	void DrawLine(Step* _step);
};
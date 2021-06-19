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
	// �Ƃ肠�����̘A�ő΍�
	bool m_start = false;
	StepKind m_resKind = StepKind::NONE;
	vector<unique_ptr<Step>> m_Map;
	// �ʂ��Ă����}�X�̃C���f�b�N�X��ۊǂ��Ă����R���e�i
	stack<int> m_path;

public:
	MapComponent(GameActor* _gator);
	virtual ~MapComponent();
	virtual void update(float _deltatime);

	void LoadMap(string _filePath);
	StepKind GetResKind() { return m_resKind; }
private:
	// �����̃}�X�ƂȂ����Ă���}�X����łȂ���
	void DrawLine(Step* _step);
};
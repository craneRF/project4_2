#pragma once
#include "Component.h"

class MapComponent :public Component
{
public:
	// �}�X�̎��
	enum class StepKind
	{
		EVENT,			// �C�x���g
		BATTLE,			// �퓬
		MAXNUM,			// �����C�x���g�̎�ސ��i���̐��j
		START,			// �X�^�[�g
		GOAL,			// �S�[��
		NONE,			// ���ݒ�
	};

	// �}�X
	struct Step
	{
		int m_id = 0;					// �}�XID
		ofVec3f m_pos;					// �}�X���W
		bool m_IsSelected = false;		// �I���t���O
		StepKind m_kind;				// �}�X�̎��
		vector<Step*> m_nextStepList;	// ���i�ނ��Ƃ��ł���}�X�̃��X�g
	};

private:
	int m_selectIndex = 0;
	// �Ƃ肠�����̘A�ő΍�
	bool m_start = false;
	StepKind m_resKind = StepKind::NONE;
	// �}�b�v�̍\��
	static vector<vector<unique_ptr<Step>>> m_Map;

	// ���ݎ~�܂��Ă���}�X�̃|�C���^
	static Step* mp_currentStep;

	// �}�X���m���Ȃ���m��(%)
	const int m_ConnectPercent = 100;

	UINT timeCount = 0;
public:
	MapComponent(GameActor* _gator);
	virtual ~MapComponent();
	virtual void update();
	virtual void input();

	// CSV�t�@�C������}�b�v���ǂݍ���
	void LoadMap(string _filePath);
	// �}�b�v�̃����_������
	void CreateRandomMap();
	void CreateRandomMap2();
	void CreateStepActor();
	StepKind GetResKind() { return m_resKind; }
	void ClearMap();

private:
	void DrawLine(Step* _step);

};
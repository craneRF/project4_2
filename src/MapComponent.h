#pragma once
#include "Component.h"

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
	bool m_IsFocused = false;		// �t�H�[�J�X�t���O
	StepKind m_kind;				// �}�X�̎��
	vector<Step*> m_nextStepList;	// ���i�ނ��Ƃ��ł���}�X�̃��X�g
};

class MapState;
class MapComponent :public Component
{
	friend class InitMapState;
	friend class SelectMapState;

private:
	// �}�b�v�̍\��
	static vector<vector<unique_ptr<Step>>> m_Map;
	// ���ݎ~�܂��Ă���}�X�̃|�C���^
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
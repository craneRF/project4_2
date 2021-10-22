#pragma once
#include "ofMain.h"

class GameActor;
class Parameter;
class MapComponent;

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

class MapState
{
private:

protected:
	static int m_selectIndex;

public:
	// �}�b�v�̍\��
	static vector<vector<unique_ptr<Step>>> m_Map;
	// ���ݎ~�܂��Ă���}�X�̃|�C���^
	static Step* mp_currentStep;

	MapState() {};
	virtual ~MapState() {};
	virtual void enter(MapComponent* _mapComponent) = 0;
	virtual MapState* update(MapComponent* _mapComponent) = 0;
	virtual void exit(MapComponent* _mapComponent) = 0;

	void ClearMap();
};

// ������
class InitMapState final : public MapState {
private:
	// �}�X���m���Ȃ���m��(%)
	const int m_ConnectPercent = 100;

	void Initialize(GameActor* _mapActor);
	// �}�b�v�̃����_������
	void CreateRandomMap();
	void CreateStepActor(GameActor* _mapActor);
	void DrawLine(Step* _step);

public:

	virtual void enter(MapComponent* _mapComponent);
	virtual MapState* update(MapComponent* _mapComponent);
	virtual void exit(MapComponent* _mapComponent);
};

// �}�X�I��
class SelectMapState final : public MapState {
private:

public:
	virtual void enter(MapComponent* _mapComponent);
	virtual MapState* update(MapComponent* _mapComponent);
	virtual void exit(MapComponent* _mapComponent);
};

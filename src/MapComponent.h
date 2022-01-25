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

// �}�b�v�̎��
enum class MAP_TYPE
{
	GLASS_LAND,
	CITY,
	TYPE_NUM,
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

// �}�b�v�����Ɏg�p������
struct MapInfo
{
	// �}�X���m���Ȃ���m��(%)
	const int m_ConnectPercent;

	// �c�ő�T�C�Y
	const int m_maxRowNum;
	// �c�Œ�T�C�Y
	const int m_minRowNum;
	// ���ő�T�C�Y
	const int m_maxColNum;
	// ���Œ�T�C�Y
	const int m_minColNum;

	// �}�X�̉摜�t�@�C��
	const std::string m_stepImageFile;
	// �}�X���Ȃ����C���̉摜�t�@�C��
	const std::string m_lineImageFile;
	// �S�[���A�C�R���̉摜�t�@�C��
	const std::string m_goalIconImageFile;
	// �����C�x���g�A�C�R���̉摜�t�@�C��
	vector<string> m_iconImageFileList;

	MapInfo():
		m_ConnectPercent(100),
		m_maxRowNum(4),
		m_minRowNum(2),
		m_maxColNum(6),
		m_minColNum(6),
		m_stepImageFile("Map_icon_grass.png"),
		m_lineImageFile("Road2.png"),
		m_goalIconImageFile("zeni.png")
	{
		// �m�� >= 1%
		assert(m_ConnectPercent >= 1);
		// �ő吔 >= �Œᐔ
		assert(m_maxRowNum >= m_minRowNum);
		assert(m_maxColNum >= m_minColNum);
		// ��A�s�� >= 1
		assert(m_maxRowNum >= 1 && m_maxColNum >= 1 && m_minRowNum >= 1 && m_minColNum >= 1);
	}
	MapInfo(const int _connectPercent, const int _maxRowNum,  const int _minRowNum, const int _maxColNum,  const int _minColNum, const std::string& _stepImageFile, const std::string& _lineImageFile, const std::string _goalIconImageFile) :
		m_ConnectPercent(_connectPercent),
		m_maxRowNum(_maxRowNum),
		m_minRowNum(_minRowNum),
		m_maxColNum(_maxColNum),
		m_minColNum(_minColNum),
		m_stepImageFile(_stepImageFile),
		m_lineImageFile(_lineImageFile),
		m_goalIconImageFile(_goalIconImageFile)
	{
		// �m�� >= 1%
		assert(m_ConnectPercent >= 1);
		// �ő吔 >= �Œᐔ
		assert(m_maxRowNum >= m_minRowNum);
		assert(m_maxColNum >= m_minColNum);
		// ��A�s�� >= 1
		assert(m_maxRowNum >= 1 && m_maxColNum >= 1 && m_minRowNum >= 1 && m_minColNum >= 1);
	}
	~MapInfo() = default;
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
	// static Step* mp_currentStep;
	static stack<Step*> m_passedStepStack;

	// �}�b�v�����Ɏg�p�����񃊃X�g
	static unordered_map<MAP_TYPE, MapInfo> m_mapList;
	static MAP_TYPE m_mapType;
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
	static void BackStep();
	static const MapInfo& GetMapInfo() { return m_mapList[m_mapType]; }
};
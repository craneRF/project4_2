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

// マップの種類
enum class MAP_TYPE
{
	GLASS_LAND,
	CITY,
	TYPE_NUM,
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

// マップ生成に使用する情報
struct MapInfo
{
	// マス同士をつなげる確率(%)
	const int m_ConnectPercent;

	// 縦最大サイズ
	const int m_maxRowNum;
	// 縦最低サイズ
	const int m_minRowNum;
	// 横最大サイズ
	const int m_maxColNum;
	// 横最低サイズ
	const int m_minColNum;

	// マスの画像ファイル
	const std::string m_stepImageFile;
	// マスをつなぐラインの画像ファイル
	const std::string m_lineImageFile;
	// ゴールアイコンの画像ファイル
	const std::string m_goalIconImageFile;
	// 道中イベントアイコンの画像ファイル
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
		// 確率 >= 1%
		assert(m_ConnectPercent >= 1);
		// 最大数 >= 最低数
		assert(m_maxRowNum >= m_minRowNum);
		assert(m_maxColNum >= m_minColNum);
		// 列、行数 >= 1
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
		// 確率 >= 1%
		assert(m_ConnectPercent >= 1);
		// 最大数 >= 最低数
		assert(m_maxRowNum >= m_minRowNum);
		assert(m_maxColNum >= m_minColNum);
		// 列、行数 >= 1
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
	// マップの構造
	static vector<vector<unique_ptr<Step>>> m_Map;
	// 現在止まっているマスのポインタ
	// static Step* mp_currentStep;
	static stack<Step*> m_passedStepStack;

	// マップ生成に使用する情報リスト
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
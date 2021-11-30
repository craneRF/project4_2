#pragma once
#include "ofMain.h"

class GameActor;
class Parameter;
class MapComponent;
struct Step;
enum class StepKind;

class MapState
{
private:

protected:
	int m_selectIndex;

public:
	MapState() {};
	virtual ~MapState() {};
	virtual void enter(MapComponent* _mapComponent) = 0;
	virtual MapState* update(MapComponent* _mapComponent) = 0;
	virtual void exit(MapComponent* _mapComponent) = 0;
};

// 初期化
class InitMapState final : public MapState {
private:
	// マス同士をつなげる確率(%)
	const int m_ConnectPercent = 100;

	// 縦最大サイズ
	const int m_maxRowNum = 4;
	// 横最大サイズ
	const int m_maxColNum = 6;

	// 縦最大サイズ
	const int m_minRowNum = 2;
	// 横最低サイズ
	const int m_minColNum = 4;

	// マスの大きさ
	const float m_stepScale = 150;

	// マスの画像ファイル
	const std::string m_stepImageFile = "Map_icon_grass.png";
	//const std::string m_stepImageFile = "Map_icon_city.png";
	// マスをつなぐラインの画像ファイル
	const std::string m_lineImageFile = "Road2.png";
	//const std::string m_lineImageFile = "Road.png";

	void Initialize(GameActor* _mapActor);
	// マップのランダム生成
	void CreateRandomMap();
	void CreateStepActor(GameActor* _mapActor);
	void CreateLineActor(GameActor* _mapActor);
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

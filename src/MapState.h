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
	static ofVec3f m_golaPos;

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
	// マスの大きさ
	const float m_stepScale = 150;
	// アイコンの大きさ
	const float m_iconScale = 150;
	// キャラアイコンの画像ファイル
	const std::string m_charaIconImageFile = "knight.png";

	void Initialize(GameActor* _mapActor);
	// マップのランダム生成
	void CreateRandomMap(const struct MapInfo& _mapInfo);
	void CreateStepActor(GameActor* _mapActor, const MapInfo& _mapInfo);
	void CreateLineActor(GameActor* _mapActor, const MapInfo& _mapInfo);
	void CreateIconActor(GameActor* _mapActor, const MapInfo& _mapInfo);
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

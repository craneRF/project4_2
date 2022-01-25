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

// ������
class InitMapState final : public MapState {
private:
	// �}�X�̑傫��
	const float m_stepScale = 150;
	// �A�C�R���̑傫��
	const float m_iconScale = 150;
	// �L�����A�C�R���̉摜�t�@�C��
	const std::string m_charaIconImageFile = "knight.png";

	void Initialize(GameActor* _mapActor);
	// �}�b�v�̃����_������
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

// �}�X�I��
class SelectMapState final : public MapState {
private:

public:
	virtual void enter(MapComponent* _mapComponent);
	virtual MapState* update(MapComponent* _mapComponent);
	virtual void exit(MapComponent* _mapComponent);
};

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

// ������
class InitMapState final : public MapState {
private:
	// �}�X���m���Ȃ���m��(%)
	const int m_ConnectPercent = 100;

	// �c�ő�T�C�Y
	const int m_maxRowNum = 4;
	// ���ő�T�C�Y
	const int m_maxColNum = 6;

	// �c�ő�T�C�Y
	const int m_minRowNum = 2;
	// ���Œ�T�C�Y
	const int m_minColNum = 4;

	// �}�X�̑傫��
	const float m_stepScale = 150;

	// �}�X�̉摜�t�@�C��
	const std::string m_stepImageFile = "Map_icon_grass.png";
	//const std::string m_stepImageFile = "Map_icon_city.png";
	// �}�X���Ȃ����C���̉摜�t�@�C��
	const std::string m_lineImageFile = "Road2.png";
	//const std::string m_lineImageFile = "Road.png";

	void Initialize(GameActor* _mapActor);
	// �}�b�v�̃����_������
	void CreateRandomMap();
	void CreateStepActor(GameActor* _mapActor);
	void CreateLineActor(GameActor* _mapActor);
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

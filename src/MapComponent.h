#pragma once
#include "Component.h"

enum class StepKind;
class MapState;
class MapComponent :public Component
{
private:
	static unique_ptr<MapState> mp_mapState;
	// ƒ}ƒX“¯Žm‚ð‚Â‚È‚°‚éŠm—¦(%)
	const int m_ConnectPercent = 100;
	StepKind m_stepKind;


public:
	MapComponent(GameActor* _gator);
	virtual ~MapComponent();
	virtual void update(float _deltatime);
	virtual void input(float _deltatime);

	void Initialize();
	void SetResKind(StepKind _stepKind) { m_stepKind = _stepKind; }
	StepKind GetResKind() { return m_stepKind; }
	void ClearMap();
};
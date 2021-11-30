#include "MapComponent.h"
#include "ofApp.h"
#include "SpriteComponent.h"
#include "MapState.h"

vector<vector<unique_ptr<Step>>> MapComponent::m_Map;
Step* MapComponent::mp_currentStep = nullptr;

MapComponent::MapComponent(GameActor* _gactor) :
	Component(_gactor, "MapComponent")
{
}

MapComponent::~MapComponent()
{
}

void MapComponent::update(float _deltatime)
{
	m_stepKind = StepKind::NONE;

	auto state = mp_mapState->update(this);
	if (state)
	{
		mp_mapState->exit(this);
		mp_mapState.reset(state);
		mp_mapState->enter(this);
	}
}

void MapComponent::input(float _deltatime)
{
}

void MapComponent::Initialize()
{
	auto state = new InitMapState();
	mp_mapState.reset(state);
	mp_mapState->enter(this);
}

void MapComponent::ClearMap()
{
	m_Map.clear();
	mp_currentStep = nullptr;
}

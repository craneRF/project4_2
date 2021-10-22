#include "MapComponent.h"
#include "ofApp.h"
#include "SpriteComponent.h"
#include "MapState.h"

unique_ptr<MapState> MapComponent::mp_mapState = nullptr;


MapComponent::MapComponent(GameActor* _gactor) :
	Component(_gactor, "MapComponent")
{
	// Šm—¦‚Í1%ˆÈã‚Å‚ ‚é‚±‚Æ
	assert(m_ConnectPercent > 0);
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
	mp_mapState->ClearMap();
	mp_mapState.reset();
	mp_gActor->RemoveAllChild<GameActor>();
}

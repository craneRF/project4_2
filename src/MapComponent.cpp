#include "MapComponent.h"
#include "ofApp.h"
#include "SpriteComponent.h"
#include "MapState.h"

vector<vector<unique_ptr<Step>>> MapComponent::m_Map;
stack<Step*> MapComponent::m_passedStepStack;

unordered_map<MAP_TYPE, MapInfo> MapComponent::m_mapList;
MAP_TYPE MapComponent::m_mapType = MAP_TYPE::GLASS_LAND;

MapComponent::MapComponent(GameActor* _gactor) :
	Component(_gactor, "MapComponent")
{
	// 一度だけ初期化
	if (m_mapList.empty()) {
		vector<string> iconImageFileList;
		iconImageFileList.reserve(static_cast<int>(StepKind::MAXNUM));
		iconImageFileList.emplace_back("iconEvent.png");
		iconImageFileList.emplace_back("iconBattle.png");

		// 草原
		{
			m_mapList.emplace(std::piecewise_construct,
				std::forward_as_tuple(MAP_TYPE::GLASS_LAND),
				std::forward_as_tuple(100, 4, 2, 6, 6, "Map_icon_grass.png", "Road2.png", "enemy_boss_head0.png"));
			m_mapList[MAP_TYPE::GLASS_LAND].m_iconImageFileList = iconImageFileList;
		}
		// 街
		m_mapList.emplace(std::piecewise_construct,
			std::forward_as_tuple(MAP_TYPE::CITY),
			std::forward_as_tuple(100, 4, 2, 6, 6, "Map_icon_city.png", "Road.png", "enemy_boss_head0.png"));
		m_mapList[MAP_TYPE::CITY].m_iconImageFileList = iconImageFileList;
	}

	// マップの種類を決定
	if (m_Map.empty()) {
		m_mapType = static_cast<MAP_TYPE>(rand() % static_cast<int>(MAP_TYPE::TYPE_NUM));
	}
}

MapComponent::~MapComponent()
{
}

void MapComponent::update()
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

void MapComponent::input()
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
	//mp_currentStep = nullptr;
	stack<Step*> stackForSwap;
	m_passedStepStack.swap(stackForSwap);
}

void MapComponent::BackStep()
{
	// スタートマス以外も入っているかチェック
	if (m_passedStepStack.size() <= 1) {
		return;
	}

	m_passedStepStack.top()->m_IsSelected = false;
	m_passedStepStack.pop();
}

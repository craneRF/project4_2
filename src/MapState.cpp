#include "MapState.h"
#include "MapComponent.h"
#include "SpriteComponent.h"
#include "ofApp.h"

void InitMapState::Initialize(GameActor* _mapActor)
{
	// 確率は1%以上であること
	assert(m_ConnectPercent > 0);

	if (MapComponent::m_Map.empty())
	{
		CreateRandomMap();
	}

	// マップの描画
	//_mapActor->drawfuncVec.emplace_back([this]
	//	{

	//		for (auto & colStepList : MapComponent::m_Map)
	//		{
	//			for (auto & rowStep : colStepList)
	//			{
	//				//DrawLine(rowStep.get());
	//			}
	//		}
	//	});

	CreateLineActor(_mapActor);
	CreateStepActor(_mapActor);

	ofApp::getInstance()->mp_soundManager->setVolume(3, 0.4f);
	ofApp::getInstance()->mp_soundManager->setVolume(4, 0.4f);
}

void InitMapState::CreateRandomMap()
{
	MapComponent::ClearMap();

	assert(m_maxRowNum > 0 && m_maxColNum > 0 && m_minRowNum > 0 && m_minColNum > 0);

	// カウント変数
	int count = 0;

	// 列数のランダム生成
	const int randColNum = max(rand() % m_maxColNum, m_minColNum);


	// X座標決定に使用する割合
	const float WPR = Define::FULLWIN_W / (randColNum + 1);

	// つながれていないマスが出ないようにするために使うリスト
	vector<vector<bool>> isConnectedList;

	isConnectedList.resize(randColNum);
	MapComponent::m_Map.resize(randColNum);
	int preRandRowNum = max(rand() % m_maxRowNum, m_minRowNum);
	for (int c = 0; c < randColNum; ++c)
	{
		// スタートマス＆ゴールマス
		if (c == 0 || c == randColNum - 1)
		{
			isConnectedList[c].resize(1, true);
			MapComponent::m_Map[c].reserve(1);
		}
		// 道中マス
		else
		{
			// 今回の列の行数を前回の列から1行増やすか
			if (rand() % 2 == 0)
			{
				++preRandRowNum;
				if (preRandRowNum > m_maxRowNum)
				{
					preRandRowNum = m_maxRowNum;
				}
			}
			// 減らすか
			else
			{
				--preRandRowNum;
				if (preRandRowNum < m_minRowNum)
				{
					preRandRowNum = m_minRowNum;
				}
			}
			isConnectedList[c].resize(preRandRowNum, false);
			MapComponent::m_Map[c].reserve(preRandRowNum);
		}
	}

	// マス情報の設定
	for (int c = 0; c < randColNum; ++c)
	{
		const int size = MapComponent::m_Map[c].capacity();
		// Y座標決定に使用する割合
		const float HPR = Define::FULLWIN_H / (size + 1);

		for (int r = 0; r < size; ++r, ++count)
		{

			auto step = make_unique<Step>();
			step->m_id = count;

			// スタートマス
			if (c == 0)
			{
				step->m_kind = StepKind::START;
				step->m_IsSelected = true;
				step->m_pos = { WPR * (c + 1), Define::FULLWIN_H * 0.5f };
				MapComponent::mp_currentStep = step.get();
			}
			// ゴールマス
			else if (c == randColNum - 1)
			{
				step->m_kind = StepKind::GOAL;
				step->m_IsSelected = false;
				step->m_pos = { WPR * (c + 1), Define::FULLWIN_H * 0.5f };
			}
			// 道中マス
			else
			{
				step->m_kind = static_cast<StepKind>(rand() % static_cast<int>(StepKind::MAXNUM));
				step->m_IsSelected = false;
				step->m_pos = { WPR * (c + 1), HPR * (r + 1) };
			}

			MapComponent::m_Map[c].emplace_back(move(step));
		}
	}

	// マスの接続
	for (int c = 0; c < randColNum; ++c)
	{
		// ゴールマス
		if (c == randColNum - 1)
		{
			continue;
		}

		for (int r = 0; r < MapComponent::m_Map[c].size(); ++r)
		{
			// スタートマス
			if (c == 0)
			{
				for (int i = 0, size = MapComponent::m_Map[1].size(); i < size; ++i)
				{
					MapComponent::m_Map[0][0]->m_nextStepList.emplace_back(MapComponent::m_Map[1][i].get());
					isConnectedList[1][i] = true;
				}
			}
			// ゴール手前マス
			else if (c == randColNum - 2)
			{
				MapComponent::m_Map[c][r]->m_nextStepList.emplace_back(MapComponent::m_Map.back()[0].get());
			}
			// 道中マス
			else
			{
				// 行き止まり防止で最低1つのマスとつながるようにする
				bool isNeverSet = true;
				for (int i = r - 1; i < r + 2; ++i)
				{
					if (i < 0 || i >= MapComponent::m_Map[c + 1].size())
					{
						continue;
					}

					// 確率で線をつながない
					if (rand() % 100 >= m_ConnectPercent)
					{
						// すでに一つ以上のマスとつながっている OR 今回のループはまだ最後ではない(次のループでマスとつながる可能性が残っている)
						if (!isNeverSet || i + 1 < r + 1)
						{
							continue;
						}
					}

					MapComponent::m_Map[c][r]->m_nextStepList.emplace_back(MapComponent::m_Map[c + 1][i].get());
					isConnectedList[c + 1][i] = true;
					isNeverSet = false;
				}
			}
		}


		// 順番に選択ができるようにソート
		for (int r = 0, size = MapComponent::m_Map[c].size(); r < size; ++r)
		{
			sort(MapComponent::m_Map[c][r]->m_nextStepList.begin(), MapComponent::m_Map[c][r]->m_nextStepList.end(), [](const Step* a, const Step* b) {
				return a->m_id < b->m_id;
				});
		}
	}
}

void InitMapState::CreateStepActor(GameActor * _mapActor)
{
	auto width = ofApp::getInstance()->mp_texture->GetImage("images/" + m_stepImageFile)->getWidth();
	// スケール
	const float scale = m_stepScale / width;

	for (const auto & mapColList : MapComponent::m_Map)
	{
		for (const auto & step : mapColList)
		{
			auto actor = _mapActor->addChild<GameActor>();
			actor->initialize({}, "step" + to_string(step->m_id));
			actor->SetParam(step->m_pos, { scale,scale }, 0.0);

			auto spriteCpnt = actor->addComponent<SpriteComponent>();
			spriteCpnt->initialize(m_stepImageFile);
			spriteCpnt->AlignPivotCenter();
			if (step->m_IsSelected)
			{
				spriteCpnt->Color() = ofColor::gray;
			}
		}
	}
}

void InitMapState::CreateLineActor(GameActor * _mapActor)
{
	auto width = ofApp::getInstance()->mp_texture->GetImage("images/" + m_lineImageFile)->getWidth();

	int colCount = 0;
	int rowCount = 0;
	for (const auto & mapColList : MapComponent::m_Map)
	{
		for (const auto & step : mapColList)
		{
			for (const auto & nextStep : step->m_nextStepList)
			{
				auto vec = nextStep->m_pos - step->m_pos;
				// 回転
				float angle = RAD_TO_DEG * atan2f(-vec.y, vec.x);
				// スケール
				const float scale = vec.length() / width;

				// アクター作成
				auto actor = _mapActor->addChild<GameActor>();
				actor->initialize({}, "line" + to_string(colCount) + "_" + to_string(rowCount));
				actor->SetParam(step->m_pos + vec * 0.5f, { scale,scale }, angle);

				// スプライトコンポーネント
				auto spriteCpnt = actor->addComponent<SpriteComponent>();
				spriteCpnt->initialize(m_lineImageFile);
				spriteCpnt->AlignPivotCenter();

				actor->drawfuncVec.emplace_back([spriteCpnt, &step, nextStep]
					{
						if (step->m_IsSelected && (nextStep->m_IsFocused || nextStep->m_IsSelected))
						{
							spriteCpnt->Color() = ofColor::gray;
						}
						else
						{
							spriteCpnt->Color() = ofColor::white;
						}
					}
				);
			}

			++rowCount;
		}

		++colCount;
	}
}

void InitMapState::enter(MapComponent* _mapComponent)
{
	Initialize(_mapComponent->gActor());
}

MapState * InitMapState::update(MapComponent* _mapComponent)
{
	return new SelectMapState();
}

void InitMapState::exit(MapComponent* _mapComponent)
{
}

void SelectMapState::enter(MapComponent* _mapComponent)
{
}

MapState * SelectMapState::update(MapComponent* _mapComponent)
{
	bool down = ofApp::getInstance()->mp_inputManager->getButtonDown("Down");
	bool up = ofApp::getInstance()->mp_inputManager->getButtonDown("Up");
	bool start = ofApp::getInstance()->mp_inputManager->getButtonDown("Start");

	// 次のマスを選択（現在のマスがつながっているマスから選択）
	if (down)
	{
		ofApp::getInstance()->mp_soundManager->play(3);

		m_selectIndex++;
		if (m_selectIndex >= MapComponent::mp_currentStep->m_nextStepList.size())
		{
			m_selectIndex = 0;
		}
	}
	else if (up)
	{
		ofApp::getInstance()->mp_soundManager->play(3);

		m_selectIndex--;
		if (m_selectIndex < 0)
		{
			m_selectIndex = MapComponent::mp_currentStep->m_nextStepList.size() - 1;
		}
	}

	for (auto & nextStep : MapComponent::mp_currentStep->m_nextStepList)
	{
		nextStep->m_IsFocused = false;
	}
	MapComponent::mp_currentStep->m_nextStepList[m_selectIndex]->m_IsFocused = true;


	// 決定
	if (start)
	{
		ofApp::getInstance()->mp_soundManager->play(4);

		MapComponent::mp_currentStep = MapComponent::mp_currentStep->m_nextStepList[m_selectIndex];
		MapComponent::mp_currentStep->m_IsSelected = true;
		MapComponent::mp_currentStep->m_IsFocused = false;
		_mapComponent->SetResKind(MapComponent::mp_currentStep->m_kind);
		m_selectIndex = 0;
	}

	return nullptr;
}

void SelectMapState::exit(MapComponent* _mapComponent)
{
}

void InitMapState::DrawLine(Step * _step)
{
	if (MapComponent::mp_currentStep->m_nextStepList.empty())
	{
		return;
	}

	// 現在カーソルを当てているマス
	auto focusStep = MapComponent::mp_currentStep->m_nextStepList[m_selectIndex];

	auto pos1 = _step->m_pos;

	//	ラインの描画
	for (const auto & step : _step->m_nextStepList)
	{
		auto pos2 = step->m_pos;
		if (_step->m_IsSelected && (step == focusStep || step->m_IsSelected))
		{
			ofSetColor(ofColor::gray);

		}
		else
		{
			ofSetColor(ofColor::white);
		}

		ofDrawLine(pos1, pos2);
	}
}

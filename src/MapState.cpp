#include "MapState.h"
#include "MapComponent.h"
#include "SpriteComponent.h"
#include "ofApp.h"

void InitMapState::Initialize(GameActor* _mapActor)
{
	// �m����1%�ȏ�ł��邱��
	assert(m_ConnectPercent > 0);

	if (MapComponent::m_Map.empty())
	{
		CreateRandomMap();
	}

	// �}�b�v�̕`��
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

	// �J�E���g�ϐ�
	int count = 0;

	// �񐔂̃����_������
	const int randColNum = max(rand() % m_maxColNum, m_minColNum);


	// X���W����Ɏg�p���銄��
	const float WPR = Define::FULLWIN_W / (randColNum + 1);

	// �Ȃ���Ă��Ȃ��}�X���o�Ȃ��悤�ɂ��邽�߂Ɏg�����X�g
	vector<vector<bool>> isConnectedList;

	isConnectedList.resize(randColNum);
	MapComponent::m_Map.resize(randColNum);
	int preRandRowNum = max(rand() % m_maxRowNum, m_minRowNum);
	for (int c = 0; c < randColNum; ++c)
	{
		// �X�^�[�g�}�X���S�[���}�X
		if (c == 0 || c == randColNum - 1)
		{
			isConnectedList[c].resize(1, true);
			MapComponent::m_Map[c].reserve(1);
		}
		// �����}�X
		else
		{
			// ����̗�̍s����O��̗񂩂�1�s���₷��
			if (rand() % 2 == 0)
			{
				++preRandRowNum;
				if (preRandRowNum > m_maxRowNum)
				{
					preRandRowNum = m_maxRowNum;
				}
			}
			// ���炷��
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

	// �}�X���̐ݒ�
	for (int c = 0; c < randColNum; ++c)
	{
		const int size = MapComponent::m_Map[c].capacity();
		// Y���W����Ɏg�p���銄��
		const float HPR = Define::FULLWIN_H / (size + 1);

		for (int r = 0; r < size; ++r, ++count)
		{

			auto step = make_unique<Step>();
			step->m_id = count;

			// �X�^�[�g�}�X
			if (c == 0)
			{
				step->m_kind = StepKind::START;
				step->m_IsSelected = true;
				step->m_pos = { WPR * (c + 1), Define::FULLWIN_H * 0.5f };
				MapComponent::mp_currentStep = step.get();
			}
			// �S�[���}�X
			else if (c == randColNum - 1)
			{
				step->m_kind = StepKind::GOAL;
				step->m_IsSelected = false;
				step->m_pos = { WPR * (c + 1), Define::FULLWIN_H * 0.5f };
			}
			// �����}�X
			else
			{
				step->m_kind = static_cast<StepKind>(rand() % static_cast<int>(StepKind::MAXNUM));
				step->m_IsSelected = false;
				step->m_pos = { WPR * (c + 1), HPR * (r + 1) };
			}

			MapComponent::m_Map[c].emplace_back(move(step));
		}
	}

	// �}�X�̐ڑ�
	for (int c = 0; c < randColNum; ++c)
	{
		// �S�[���}�X
		if (c == randColNum - 1)
		{
			continue;
		}

		for (int r = 0; r < MapComponent::m_Map[c].size(); ++r)
		{
			// �X�^�[�g�}�X
			if (c == 0)
			{
				for (int i = 0, size = MapComponent::m_Map[1].size(); i < size; ++i)
				{
					MapComponent::m_Map[0][0]->m_nextStepList.emplace_back(MapComponent::m_Map[1][i].get());
					isConnectedList[1][i] = true;
				}
			}
			// �S�[����O�}�X
			else if (c == randColNum - 2)
			{
				MapComponent::m_Map[c][r]->m_nextStepList.emplace_back(MapComponent::m_Map.back()[0].get());
			}
			// �����}�X
			else
			{
				// �s���~�܂�h�~�ōŒ�1�̃}�X�ƂȂ���悤�ɂ���
				bool isNeverSet = true;
				for (int i = r - 1; i < r + 2; ++i)
				{
					if (i < 0 || i >= MapComponent::m_Map[c + 1].size())
					{
						continue;
					}

					// �m���Ő����Ȃ��Ȃ�
					if (rand() % 100 >= m_ConnectPercent)
					{
						// ���łɈ�ȏ�̃}�X�ƂȂ����Ă��� OR ����̃��[�v�͂܂��Ō�ł͂Ȃ�(���̃��[�v�Ń}�X�ƂȂ���\�����c���Ă���)
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


		// ���ԂɑI�����ł���悤�Ƀ\�[�g
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
	// �X�P�[��
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
				// ��]
				float angle = RAD_TO_DEG * atan2f(-vec.y, vec.x);
				// �X�P�[��
				const float scale = vec.length() / width;

				// �A�N�^�[�쐬
				auto actor = _mapActor->addChild<GameActor>();
				actor->initialize({}, "line" + to_string(colCount) + "_" + to_string(rowCount));
				actor->SetParam(step->m_pos + vec * 0.5f, { scale,scale }, angle);

				// �X�v���C�g�R���|�[�l���g
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

	// ���̃}�X��I���i���݂̃}�X���Ȃ����Ă���}�X����I���j
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


	// ����
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

	// ���݃J�[�\���𓖂ĂĂ���}�X
	auto focusStep = MapComponent::mp_currentStep->m_nextStepList[m_selectIndex];

	auto pos1 = _step->m_pos;

	//	���C���̕`��
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

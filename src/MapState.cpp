#include "MapState.h"
#include "MapComponent.h"
#include "SpriteComponent.h"
#include "ofApp.h"

int MapState::m_selectIndex = 0;
Step* MapState::mp_currentStep = nullptr;
vector<vector<unique_ptr<Step>>> MapState::m_Map;

void InitMapState::Initialize(GameActor* _mapActor)
{
	// �}�b�v�̕`��
	_mapActor->drawfuncVec.emplace_back ([this]
	{
		for (auto & colStepList : m_Map)
		{
			for (auto & rowStep : colStepList)
			{
				DrawLine(rowStep.get());
			}
		}
	});

	if (m_Map.empty())
	{
		CreateRandomMap();
	}
	CreateStepActor(_mapActor);
}

void InitMapState::CreateRandomMap()
{
	m_Map.clear();

	// �c���ő�T�C�Y
	constexpr int maxRowNum = 4;
	constexpr int maxColNum = 6;

	// �c���Œ�T�C�Y
	constexpr int minRowNum = 2;
	constexpr int minColNum = 4;
	assert(maxRowNum > 0 && maxColNum > 0 && minRowNum > 0 && minColNum > 0);

	// �J�E���g�ϐ�
	int count = 0;

	// �񐔂̃����_������
	const int randColNum = max(rand() % maxColNum, minColNum);


	// X���W����Ɏg�p���銄��
	const float WPR = Define::FULLWIN_W / (randColNum + 3);

	// �Ȃ���Ă��Ȃ��}�X���o�Ȃ��悤�ɂ��邽�߂Ɏg�����X�g
	vector<vector<bool>> isConnectedList;

	isConnectedList.resize(randColNum);
	m_Map.resize(randColNum);
	int preRandRowNum = max(rand() % maxRowNum, minRowNum);
	for (int c = 0; c < randColNum; ++c)
	{
		// �X�^�[�g�}�X���S�[���}�X
		if (c == 0 || c == randColNum - 1)
		{
			isConnectedList[c].resize(1, true);
			m_Map[c].reserve(1);
		}
		// �����}�X
		else
		{
			// ����̗�̍s����O��̗񂩂�1�s���₷��
			if (rand() % 2 == 0)
			{
				++preRandRowNum;
				if (preRandRowNum > maxRowNum)
				{
					preRandRowNum = maxRowNum;
				}
			}
			// ���炷��
			else
			{
				--preRandRowNum;
				if (preRandRowNum < minRowNum)
				{
					preRandRowNum = minRowNum;
				}
			}
			isConnectedList[c].resize(preRandRowNum, false);
			m_Map[c].reserve(preRandRowNum);
		}
	}

	// �}�X���̐ݒ�
	for (int c = 0; c < randColNum; ++c)
	{
		const int size = m_Map[c].capacity();
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
				step->m_pos = { WPR, Define::FULLWIN_H * 0.5f };
				mp_currentStep = step.get();
			}
			// �S�[���}�X
			else if (c == randColNum - 1)
			{
				step->m_kind = StepKind::GOAL;
				step->m_IsSelected = false;
				step->m_pos = { WPR * (randColNum + 2), Define::FULLWIN_H * 0.5f };
			}
			// �����}�X
			else
			{
				step->m_kind = static_cast<StepKind>(rand() % static_cast<int>(StepKind::MAXNUM));
				step->m_IsSelected = false;
				step->m_pos = { WPR * (c + 2), HPR * (r + 1) };
			}

			m_Map[c].emplace_back(move(step));
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

		for (int r = 0; r < m_Map[c].size(); ++r)
		{
			// �X�^�[�g�}�X
			if (c == 0)
			{
				for (int i = 0, size = m_Map[1].size(); i < size; ++i)
				{
					m_Map[0][0]->m_nextStepList.emplace_back(m_Map[1][i].get());
					isConnectedList[1][i] = true;
				}
			}
			// �S�[����O�}�X
			else if (c == randColNum - 2)
			{
				m_Map[c][r]->m_nextStepList.emplace_back(m_Map.back()[0].get());
			}
			// �����}�X
			else
			{
				// �s���~�܂�h�~�ōŒ�1�̃}�X�ƂȂ���悤�ɂ���
				bool isNeverSet = true;
				for (int i = r - 1; i < r + 2; ++i)
				{
					if (i < 0 || i >= m_Map[c + 1].size())
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

					m_Map[c][r]->m_nextStepList.emplace_back(m_Map[c + 1][i].get());
					isConnectedList[c + 1][i] = true;
					isNeverSet = false;
				}
			}
		}


		// ���ԂɑI�����ł���悤�Ƀ\�[�g
		for (int r = 0, size = m_Map[c].size(); r < size; ++r)
		{
			sort(m_Map[c][r]->m_nextStepList.begin(), m_Map[c][r]->m_nextStepList.end(), [](const Step* a, const Step* b) {
				return a->m_id < b->m_id;
				});
		}
	}
}

void InitMapState::CreateStepActor(GameActor * _mapActor)
{
	for (const auto & mapColList : m_Map)
	{
		for (const auto & step : mapColList)
		{
			auto actor = _mapActor->addChild<GameActor>();
			actor->initialize({}, "step" + to_string(step->m_id));
			actor->SetParam(step->m_pos, { 0.05f,0.05f }, 0.0);

			auto spriteCpnt = actor->addComponent<SpriteComponent>();
			spriteCpnt->initialize("Map_icon_grass.png");
			spriteCpnt->AlignPivotCenter();
			if (step->m_IsSelected)
			{
				spriteCpnt->Color() = ofColor::gray;
			}
		}
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
		m_selectIndex++;
		if (m_selectIndex >= mp_currentStep->m_nextStepList.size())
		{
			m_selectIndex = 0;
		}
	}
	else if (up)
	{
		m_selectIndex--;
		if (m_selectIndex < 0)
		{
			m_selectIndex = mp_currentStep->m_nextStepList.size() - 1;
		}
	}
	// ����
	else if (start)
	{
		mp_currentStep = mp_currentStep->m_nextStepList[m_selectIndex];
		mp_currentStep->m_IsSelected = true;
		_mapComponent->SetResKind(mp_currentStep->m_kind);
		m_selectIndex = 0;
	}

	return nullptr;
}

void SelectMapState::exit(MapComponent* _mapComponent)
{
}

void InitMapState::DrawLine(Step * _step)
{
	if (mp_currentStep->m_nextStepList.empty())
	{
		return;
	}

	// ���݃J�[�\���𓖂ĂĂ���}�X��ID
	auto forcusStep = mp_currentStep->m_nextStepList[m_selectIndex];

	auto pos1 = _step->m_pos;

	//	���C���̕`��
	for (const auto & step : _step->m_nextStepList)
	{
		if (!step)
		{
			continue;
		}

		auto pos2 = step->m_pos;
		if (_step->m_IsSelected && (step == forcusStep || step->m_IsSelected))
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

void MapState::ClearMap()
{
	m_Map.clear();
	mp_currentStep = nullptr;
}
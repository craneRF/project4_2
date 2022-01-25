#include "MapState.h"
#include "MapComponent.h"
#include "SpriteComponent.h"
#include "ofApp.h"

ofVec3f MapState::m_golaPos = { 0,0,0 };

void InitMapState::Initialize(GameActor* _mapActor)
{
	auto& mapInfo = MapComponent::GetMapInfo();

	if (MapComponent::m_Map.empty())
	{
		CreateRandomMap(mapInfo);
	}

	CreateLineActor(_mapActor, mapInfo);
	CreateStepActor(_mapActor, mapInfo);
	CreateIconActor(_mapActor, mapInfo);

	ofApp::getInstance()->mp_soundManager->setVolume(3, 0.4f);
	ofApp::getInstance()->mp_soundManager->setVolume(4, 0.4f);
}

void InitMapState::CreateRandomMap(const MapInfo& _mapInfo)
{
	// �J�E���g�ϐ�
	int count = 0;

	// �񐔂̃����_������
	const int randColNum = max(rand() % _mapInfo.m_maxColNum, _mapInfo.m_minColNum);


	// X���W����Ɏg�p���銄��
	const float WPR = Define::FULLWIN_W / (randColNum + 1);

	// �Ȃ���Ă��Ȃ��}�X���o�Ȃ��悤�ɂ��邽�߂Ɏg�����X�g
	vector<vector<bool>> isConnectedList;

	isConnectedList.resize(randColNum);
	MapComponent::m_Map.resize(randColNum);
	int preRandRowNum = max(rand() % _mapInfo.m_maxRowNum, _mapInfo.m_minRowNum);
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
				if (preRandRowNum > _mapInfo.m_maxRowNum)
				{
					preRandRowNum = _mapInfo.m_maxRowNum;
				}
			}
			// ���炷��
			else
			{
				--preRandRowNum;
				if (preRandRowNum < _mapInfo.m_minRowNum)
				{
					preRandRowNum = _mapInfo.m_minRowNum;
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
				MapComponent::m_passedStepStack.push(step.get());
			}
			// �S�[���}�X
			else if (c == randColNum - 1)
			{
				step->m_kind = StepKind::GOAL;
				step->m_IsSelected = false;
				step->m_pos = { WPR * (c + 1), Define::FULLWIN_H * 0.5f };
				m_golaPos = step->m_pos;
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
					if (rand() % 100 >= _mapInfo.m_ConnectPercent)
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

void InitMapState::CreateStepActor(GameActor * _mapActor, const MapInfo& _mapInfo)
{
	auto width = ofApp::getInstance()->mp_texture->GetImage("images/" + _mapInfo.m_stepImageFile)->getWidth();
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
			spriteCpnt->initialize(_mapInfo.m_stepImageFile);
			spriteCpnt->AlignPivotCenter();

			actor->drawfuncVec.emplace_back([spriteCpnt, &step]
				{
					if (step->m_IsSelected || step->m_IsFocused)
					{
						spriteCpnt->Color() = ofColor::white;
					}
					else
					{
						spriteCpnt->Color() = ofColor::gray;
					}
				}
			);
		}
	}
}

void InitMapState::CreateLineActor(GameActor * _mapActor, const MapInfo& _mapInfo)
{
	auto width = ofApp::getInstance()->mp_texture->GetImage("images/" + _mapInfo.m_lineImageFile)->getWidth();

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
				spriteCpnt->initialize(_mapInfo.m_lineImageFile);
				spriteCpnt->AlignPivotCenter();

				actor->drawfuncVec.emplace_back([spriteCpnt, &step, nextStep]
					{
						if (step->m_IsSelected && (nextStep->m_IsFocused || nextStep->m_IsSelected))
						{
							spriteCpnt->Color() = ofColor::white;
						}
						else
						{
							spriteCpnt->Color() = ofColor::gray;
						}
					}
				);
			}

			++rowCount;
		}

		++colCount;
	}
}

void InitMapState::CreateIconActor(GameActor * _mapActor, const MapInfo& _mapInfo)
{
	// �I�t�Z�b�g
	const ofVec3f offset = ofVec3f(0, -20, 0);

	// �����A�C�R��
	{
		int colCount = 0;
		int rowCount = 0;
		for (const auto & mapColList : MapComponent::m_Map)
		{
			for (const auto & step : mapColList)
			{
				// �����ł͓����}�X�����Ή�
				if (static_cast<int>(step->m_kind) >= static_cast<int>(StepKind::MAXNUM)) {
					continue;
				}

				const string& imageFile = _mapInfo.m_iconImageFileList.at(static_cast<int>(step->m_kind));
				const auto size = min(ofApp::getInstance()->mp_texture->GetImage("images/" + imageFile)->getWidth(),
					ofApp::getInstance()->mp_texture->GetImage("images/" + imageFile)->getHeight());
				// �X�P�[��
				const float scale = m_iconScale / size;

				// �A�N�^�[�쐬
				auto actor = _mapActor->addChild<GameActor>();
				actor->initialize({}, "eventIcon" + to_string(colCount) + "_" + to_string(rowCount));
				actor->SetParam(step->m_pos + offset, { scale,scale });

				// �X�v���C�g�R���|�[�l���g
				auto spriteCpnt = actor->addComponent<SpriteComponent>();
				spriteCpnt->initialize(imageFile);
				spriteCpnt->AlignPivotCenter();

				actor->drawfuncVec.emplace_back([spriteCpnt, &step]
					{
						if (step->m_IsSelected || step->m_IsFocused)
						{
							spriteCpnt->Color() = ofColor::white;
						}
						else
						{
							spriteCpnt->Color() = ofColor::gray;
						}
					}
				);
				++rowCount;
			}
			++colCount;
		}
	}

	// �S�[���A�C�R��
	{
		const auto size = min(ofApp::getInstance()->mp_texture->GetImage("images/" + _mapInfo.m_goalIconImageFile)->getWidth(),
			ofApp::getInstance()->mp_texture->GetImage("images/" + _mapInfo.m_goalIconImageFile)->getHeight());
		// �X�P�[��
		const float scale = m_iconScale / size;

		// �A�N�^�[�쐬
		auto actor = _mapActor->addChild<GameActor>();
		actor->initialize({}, "goalIcon");
		actor->SetParam(m_golaPos + offset, { scale,scale }, 0);

		// �X�v���C�g�R���|�[�l���g
		auto spriteCpnt = actor->addComponent<SpriteComponent>();
		spriteCpnt->initialize(_mapInfo.m_goalIconImageFile);
		spriteCpnt->AlignPivotCenter();
	}

	// �L�����A�C�R��
	{
		const auto size = min(ofApp::getInstance()->mp_texture->GetImage("images/" + m_charaIconImageFile)->getWidth(),
			ofApp::getInstance()->mp_texture->GetImage("images/" + m_charaIconImageFile)->getHeight());
		// �X�P�[��
		const float scale = m_iconScale / size;

		// �A�N�^�[�쐬
		auto actor = _mapActor->addChild<GameActor>();
		actor->initialize({}, "charaIcon");
		actor->SetParam(MapComponent::m_passedStepStack.top()->m_pos + offset, { scale,scale }, 0);

		// ���݃}�X�̍��W��ݒ�
		actor->drawfuncVec.emplace_back([offset, actor] {
			actor->Pos() = MapComponent::m_passedStepStack.top()->m_pos + offset;
			}
		);

		// �X�v���C�g�R���|�[�l���g
		auto spriteCpnt = actor->addComponent<SpriteComponent>();
		spriteCpnt->initialize(m_charaIconImageFile);
		spriteCpnt->AlignPivotCenter();
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
		if (m_selectIndex >= MapComponent::m_passedStepStack.top()->m_nextStepList.size())
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
			m_selectIndex = MapComponent::m_passedStepStack.top()->m_nextStepList.size() - 1;
		}
	}

	for (auto & nextStep : MapComponent::m_passedStepStack.top()->m_nextStepList)
	{
		nextStep->m_IsFocused = false;
	}
	MapComponent::m_passedStepStack.top()->m_nextStepList[m_selectIndex]->m_IsFocused = true;

	// ����
	if (start)
	{
		ofApp::getInstance()->mp_soundManager->play(4);

		MapComponent::m_passedStepStack.push(MapComponent::m_passedStepStack.top()->m_nextStepList[m_selectIndex]);
		MapComponent::m_passedStepStack.top()->m_IsSelected = true;
		MapComponent::m_passedStepStack.top()->m_IsFocused = false;
		_mapComponent->SetResKind(MapComponent::m_passedStepStack.top()->m_kind);
		m_selectIndex = 0;
	}

	return nullptr;
}

void SelectMapState::exit(MapComponent* _mapComponent)
{
}

void InitMapState::DrawLine(Step * _step)
{
	if (MapComponent::m_passedStepStack.top()->m_nextStepList.empty())
	{
		return;
	}

	// ���݃J�[�\���𓖂ĂĂ���}�X
	auto focusStep = MapComponent::m_passedStepStack.top()->m_nextStepList[m_selectIndex];

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

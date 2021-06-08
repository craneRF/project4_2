#include "MapComponent.h"
#include "ofApp.h"

MapComponent::MapComponent(GameActor* _gactor) :
	Component(_gactor, "MapComponent")
{
	m_path.push(0);
}

MapComponent::~MapComponent()
{

}

void MapComponent::update(float _deltatime)
{
	bool down = ofApp::getInstance()->mp_inputManager->getButtonDown("Down");
	bool up = ofApp::getInstance()->mp_inputManager->getButtonDown("Up");
	bool start = ofApp::getInstance()->mp_inputManager->getButtonDown("Start");
	m_resKind = StepKind::NONE;
	int currentIndex = m_path.top();
	
	// 次のマスを選択（現在のマスがつながっているマスから選択）
	if (down)
	{
		m_selectIndex++;
		if (m_selectIndex >= m_Map[currentIndex]->m_nextIndex.size())
		{
			m_selectIndex = 0;
		}
	}
	else if (up)
	{
		m_selectIndex--;
		if (m_selectIndex < 0)
		{
			m_selectIndex = m_Map[currentIndex]->m_nextIndex.size() - 1;
		}
	}
	// 決定
	else if (start)
	{
		if (m_start)
		{
			m_path.push(m_Map[currentIndex]->m_nextIndex[m_selectIndex]);
			currentIndex = m_path.top();
			m_resKind = m_Map[currentIndex]->m_kind;
			m_Map[currentIndex]->m_IsSelected = true;
			m_selectIndex = 0;
		}
		else
		{
			m_start = true;
		}
	}

	// マップの描画
	mp_gActor->drawfunc = [&, currentIndex]
	{
		int stepNum = m_Map.size();
		int index = m_Map[currentIndex]->m_nextIndex[m_selectIndex];
		for (int i = 0; i < stepNum; i++)
		{
			auto step = m_Map[i].get();

			// すでに通った or 現在選択中
			if (step->m_IsSelected || index == m_Map[i]->m_index)
			{
				ofSetColor(ofColor::green);
				ofDrawRectangle(step->m_pos, 30, 30);
				ofSetColor(ofColor::gray);
				DrawLine(step);
			}
			else
			{
				ofSetColor(ofColor::lightGreen);
				ofDrawRectangle(step->m_pos, 30, 30);
				ofSetColor(ofColor::white);
				DrawLine(step);
			}
		}

	};

}

void MapComponent::DrawLine(Step * _step)
{
	for (int & index : _step->m_nextIndex)
	{
		if (index < 0)
			continue;

		auto pos1 = _step->m_pos;
		auto pos2 = m_Map[index]->m_pos;
		pos1 += {15.f, 15.f, 0.f};
		pos2 += {15.f, 15.f, 0.f};
		ofDrawLine(pos1, pos2);
	}
}

void MapComponent::LoadMap(string _filePath)
{
	ifstream fin(_filePath);
	if (!fin)
	{
		cout << "マップ読み込み失敗\n";
		return;
	}

	const char _delimiter = ',';
	while (!fin.eof())
	{
		std::string buffer;
		fin >> buffer;

		std::list<std::string> record;
		std::istringstream streamBuffer(buffer);
		std::string token;

		while (std::getline(streamBuffer, token, _delimiter)) {
			if (token == "")
				break;

			record.emplace_back(token);
		}

		int num = record.size() / 4;
		while (!record.empty())
		{
			for (int i = 0; i < num; i++)
			{
				auto step = make_unique<Step>();

				// インデックス
				step->m_index = stoi(record.front());
				record.pop_front();

				// タイプ
				if (record.front() == "START")
				{
					step->m_kind = StepKind::START;
				}
				else if (record.front() == "GOAL")
				{
					step->m_kind = StepKind::GOAL;
				}
				else if (record.front() == "EVENT")
				{
					step->m_kind = StepKind::EVENT;
				}
				else if (record.front() == "BATTLE")
				{
					step->m_kind = StepKind::BATTLE;
				}
				else
				{
					step->m_kind = StepKind::NONE;
				}
				record.pop_front();

				// 座標
				string data = record.front();
				record.pop_front();
				float x = stof(data.substr(0, 3)) * Define::WIN_W;
				data.erase(0, 3);
				int pos = data.find('/');
				float y = stof(data.substr(pos + 1, 3))* Define::WIN_H;
				step->m_pos = { x, y };

				// 次のマス
				data = record.front();
				record.pop_front();
				pos = data.find('/');
				if (pos == string::npos)
				{
					step->m_nextIndex.emplace_back(stoi(data));
				}
				else
				{
					while (!data.empty())
					{
						step->m_nextIndex.emplace_back(atoi(&data.front()));

						//step->m_nextRow.emplace_back(stoi(data.substr(0, pos)));
						data.erase(0, 2);
						//pos = data.find('/');
					}
				}


				m_Map.push_back(move(step));
			}
		}
	}
}

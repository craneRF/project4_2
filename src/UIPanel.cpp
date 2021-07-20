#include "UIPanel.h"

UIPanel::UIPanel(string _name)
	:UIActor(_name)
{
	m_UIchildList.clear();
}

UIPanel::~UIPanel()
{
}

void UIPanel::update(float _deltaTime)
{
	Actor::caluculateWorldTransform();

	//削除予定UIアクターの削除
	m_UIchildList.erase(
		remove_if(m_UIchildList.begin(), m_UIchildList.end(),
			[](const auto& uic) {return uic->GetActorState() == ActorState::EErace; }),
		m_UIchildList.end()
	);

	//追加待ちUIアクターの追加処理
	while (!m_UIchildAddQue.empty()) {
		m_UIchildList.push_back(move(m_UIchildAddQue.front()));
		m_UIchildAddQue.pop();
	}
	//子UIアクターの全件処理
	for (auto& uic : m_UIchildList)
	{
		if (uic->GetActorState() != ActorState::EPause) {
			uic->update(_deltaTime);  //描画に影響する処理などはEActive状態とEDrawing状態の時に行う
		}
	}
}

void UIPanel::input(float _deltaTime)
{
	for (auto& uic : m_UIchildList)
	{
		if (uic->GetActorState() == ActorState::EActive) {
			uic->input(_deltaTime);  //操作処理はEActive状態のUIScreenしか行わない
		}
	}
}

void UIPanel::draw()
{
	for (auto& uic : m_UIchildList) {
		if (uic->GetActorDrawState() == ActorDrawState::EVisible) {
			uic->draw();
		}
	}

}

void UIPanel::RemoveAllChild()
{
	queue<unique_ptr<UIActor>>().swap(m_UIchildAddQue);	//queueの全消し
	for (auto& uic : m_UIchildList) {
		uic->StateErace();
	}
}
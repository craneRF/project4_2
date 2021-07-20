#include "ofApp.h"
#include "UIScreen.h"
#include "UISprite.h"

UIScreen::UIScreen(string _name)
	:m_screenName(_name)
	,m_UIScreenState(UIScreenState::EActive)
	,m_UIScreenDrawState(UIScreenDrawState::EVisible)
{
}

UIScreen::~UIScreen()
{
}

void UIScreen::initialize()
{
}

void UIScreen::update(float _deltaTime)
{
	//削除予定UIアクターの削除
	m_UIActorList.erase(
		remove_if(m_UIActorList.begin(), m_UIActorList.end(),
			[](const auto& uia) {return uia->GetActorState() == Actor::ActorState::EErace; }),
		m_UIActorList.end()
	);

	//追加待ちUIアクターの追加処理
	while (!m_UIActorAddQue.empty()) {
		m_UIActorList.push_back(move(m_UIActorAddQue.front()));
		m_UIActorAddQue.pop();
	}
	//子UIアクターの全件処理
	for (auto& uia : m_UIActorList)
	{
		if (uia->GetActorState() != Actor::ActorState::EPause) {
			uia->update(_deltaTime);  //描画に影響する処理などはEActive状態とEDrawing状態の時に行う
		}
	}
}

void UIScreen::input(float _deltaTime)
{
	for (auto& uia : m_UIActorList)
	{
		if (uia->GetActorState() == Actor::ActorState::EActive) {
			uia->input(_deltaTime);  //操作処理はEActive状態のUIScreenしか行わない
		}
	}
}

void UIScreen::draw()
{
	for (auto& uia : m_UIActorList) {
		if (uia->GetActorDrawState() == Actor::ActorDrawState::EVisible) {
			uia->draw();
		}
	}
}

void UIScreen::RemoveAllUIActor()
{
	queue<unique_ptr<UIActor>>().swap(m_UIActorAddQue);	//queueの全消し
	for (auto& uia : m_UIActorList) {
		uia->StateErace();
	}
}

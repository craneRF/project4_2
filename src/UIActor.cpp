#include "UIActor.h"

UIActor::UIActor(string _name)
	:Actor(_name)
	, mp_UIparent(nullptr)
	, mp_UIScreen(nullptr)
{
	m_UIchildList.clear();
	mp_fontRenderer = make_unique<FontRenderer>();
	mp_TexRenderer = make_unique<TextureRenderer>();
}

UIActor::~UIActor()
{
}

void UIActor::caluculateWorldTransform()
{
	if (mp_UIparent != nullptr) {
		m_worldScale = mp_UIparent->m_worldScale * m_scale;
		m_worldRotAngle = mp_UIparent->m_worldRotAngle + m_rotAngle;
		m_worldPos = mp_UIparent->m_worldPos +
			m_pos.getRotated(-mp_UIparent->m_worldRotAngle, ofVec3f(0, 0, 1)) *
			mp_UIparent->m_worldScale;
	}
	else {
		Actor::caluculateWorldTransform();
	}
}

void UIActor::update(float _deltaTime)
{
	caluculateWorldTransform();

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

void UIActor::input(float _deltaTime)
{
	for (auto& uic : m_UIchildList)
	{
		if (uic->GetActorState() == ActorState::EActive) {
			uic->input(_deltaTime);  //操作処理はEActive状態のUIScreenしか行わない
		}
	}
}

void UIActor::draw(float _deltaTime)
{
	Actor::draw();

	for (auto& uic : m_UIchildList) {
		if (uic->GetActorDrawState() == ActorDrawState::EVisible) {
			uic->draw(_deltaTime);
		}
	}

}

void UIActor::RemoveAllChild()
{
	queue<unique_ptr<UIActor>>().swap(m_UIchildAddQue);	//queueの全消し
	for (auto& uic : m_UIchildList) {
		uic->StateErace();
	}
}

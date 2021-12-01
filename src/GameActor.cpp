#include "ofApp.h"
#include "GameActor.h"
#include "stdComponent.h"

GameActor::GameActor(string _name) 
	:Actor(_name)
	,mp_parent(nullptr)
{
	m_componentList.clear();
	m_childList.clear();
}

GameActor::~GameActor()
{
}

void GameActor::caluculateWorldTransform()
{
	if (this->RotAngle() >= 360.0f) {
		this->RotAngle() = 0.0f;
	}
	else if (this->RotAngle() <= 0.0f) {
		this->RotAngle() = 360.0f;
	}

	if (mp_parent != nullptr) {
		this->WorldScale() = mp_parent->WorldScale() * this->Scale();
		this->WorldRotAngle() = mp_parent->WorldRotAngle() + this->RotAngle();
		this->WorldPos() = mp_parent->WorldPos() +
			this->Pos().getRotated(-(mp_parent->WorldRotAngle()), ofVec3f(0, 0, 1)) *
			mp_parent->WorldScale();
	}
	else {
		this->WorldScale() = this->Scale() * ((float)ofGetHeight() / (float)Define::FULLWIN_H);
		this->WorldRotAngle() = this->RotAngle();
		this->WorldPos() = this->Pos().getRotated(-this->RotAngle(), ofVec3f(0, 0, 1)) * this->Scale()* ((float)ofGetHeight() / (float)Define::FULLWIN_H);
	}
}

void GameActor::initialize(ofVec3f _pos, string _name) {
	m_pos = _pos;
	caluculateWorldTransform();
	m_name = _name;
}

//GameActor* GameActor::addChild()
//{
//	auto actor = make_unique<GameActor>();
//	auto res = actor.get();
//	m_childAddQue.push(move(actor));
//	res->mp_parent = this;
//	return res;
//}
//
//void GameActor::RemoveAllChild()
//{
//	queue<unique_ptr<GameActor>>().swap(m_childAddQue);	//queueの全消し
//	for (auto& c : m_childList) {
//		c->waitforErase_ = true;
//	}
//}
//
//GameActor* GameActor::getChild(int _index) const
//{
//	return m_childList[_index].get();
//}

GameActor * GameActor::findActor(GameActor* _current, string _name)
{
	if (_current->m_name == _name) return _current;
	for (auto & actor : _current->m_childList) {
		auto tmp = findActor(actor.get(), _name);
		if (tmp != nullptr) return tmp;
	}
	return nullptr;
}

list<GameActor*>&& GameActor::findActors(GameActor * _current, string _name, list<GameActor*>&&	_list)
{
	if (_current->m_name == _name) _list.push_back(_current);
	for (auto & actor : _current->m_childList) {
		_list = findActors(actor.get(), _name, move(_list));
	}
	return move(_list);
}

GameActor* GameActor::createMap(GameActor * _parent, ofVec3f _pos, string _name)
{
	auto mapActor = _parent->addChild<GameActor>();
	mapActor->initialize(_pos, _name);
	mapActor->addComponent<MapComponent>();

	return mapActor;
}

void GameActor::update() {
	caluculateWorldTransform();
	m_actorDelta = ofApp::getInstance()->m_deltaTime;

	if (!m_componentList.empty()) {
		m_componentList.erase(
			remove_if(m_componentList.begin(), m_componentList.end(),
				[](const auto& cpnt) { return cpnt->GetComponentState() == Component::ComponentState::EErace; }),
			m_componentList.end()
		);
	}
	//自分のコンポーネントの更新処理
	if (!m_componentList.empty()) {
		for (const auto& cpnt : m_componentList) {
			if (cpnt->GetComponentState() != Component::ComponentState::EPause) {
				cpnt->update();
			}
		}
	}
	//DrawOrder
	//ofApp::getInstance()->draworderset_.insert(this);
	//削除予定アクターの削除
	if (!m_childList.empty()) {
		m_childList.erase(
			remove_if(m_childList.begin(), m_childList.end(),
				[](const auto& gac) { return gac->GetActorState() == ActorState::EErace; }),
			m_childList.end()
		);
	}
	//追加待ちアクターの追加処理
	while (!m_childAddQue.empty()) {
		m_childList.push_back(move(m_childAddQue.front()));
		m_childAddQue.pop();
	}
	//子ゲームアクターの更新処理
	if (!m_childList.empty()) {
		for (auto& gac : m_childList) {
			if (gac->GetActorState() != ActorState::EPause) {
				gac->update();
			}
		}
	}
}

void GameActor::input()
{
	//自分のコンポーネントの入力処理
	if (!m_componentList.empty()) {
		for (const auto& cpnt : m_componentList) {
			if (cpnt->GetComponentState() == Component::ComponentState::EActive) {
				cpnt->input();
			}
		}
	}
	//子ゲームアクターの入力処理
	if (!m_childList.empty()) {
		for (auto& gac : m_childList) {
			if (gac->GetActorState() == ActorState::EActive) {
				gac->input();
			}
		}
	}
}


void GameActor::draw()
{
	if (GetActorDrawState() == ActorDrawState::EVisible) {
		for (auto& df : this->drawfuncVec) {
			assert(df != nullptr);
			ofPushMatrix();
			ofTranslate(this->m_worldPos);
			ofRotateDeg(-(this->m_worldRotAngle));
			ofScale(this->m_worldScale);
			df();
			ofPopMatrix();
		}
	}

	if (!m_childList.empty()) {
		for (auto& gac : m_childList) {
			gac->draw();
		}
	}
}
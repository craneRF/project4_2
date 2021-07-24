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

	if (mp_parent != nullptr) {
		this->WorldScale() = mp_parent->WorldScale() * this->Scale();
		this->WorldRotAngle() = mp_parent->WorldRotAngle() + this->RotAngle();
		this->WorldPos() = mp_parent->WorldPos() +
			this->Pos().getRotated(-(mp_parent->WorldRotAngle()), ofVec3f(0, 0, 1)) *
			mp_parent->WorldScale();
	}
	else {
		this->WorldScale() = this->Scale();
		this->WorldRotAngle() = this->RotAngle();
		this->WorldPos() = this->Pos().getRotated(-(this->RotAngle()), ofVec3f(0, 0, 1)) * this->Scale();
	}
}

GameActor* GameActor::createPlayer(GameActor* _parent, ofVec3f _pos, string _name)
{
	auto actor = _parent->addChild();
	actor->Pos() = _pos;
	actor->Name() = _name;
	auto moveCpnt = actor->addComponent<MoveComponent>();
	actor->drawfunc = [=]() {
		ofSetColor(ofColor::green);
		ofDrawRectangle(ofVec3f(-15, -15), 30, 30);
	};
	auto coliisionCpnt = actor->addComponent<CollisionComponent>();
	coliisionCpnt->initialize(ofVec3f(0, 0), 30, 30, CollisionType::PLAYER_OBJECT);
	coliisionCpnt->m_onCollisionFunc = bind(&onCollision, actor, std::placeholders::_1);

	return actor;
}

GameActor* GameActor::createEnemy(GameActor* _parent, ofVec3f _pos, string _name)
{
	auto actor = _parent->addChild();
	actor->Pos() = _pos;
	actor->Name() = _name;
	auto moveCpnt = actor->addComponent<MoveComponent>();
	//moveCpnt->AddMovePos({ 150.0f,0,0 });

	actor->drawfunc = [=]() {
		ofSetColor(ofColor::green);
		ofDrawRectangle(ofVec3f(-15, -15), 30, 30);
	};

	auto coliisionCpnt = actor->addComponent<CollisionComponent>();
	coliisionCpnt->initialize(ofVec3f(0, 0), 30, 30, CollisionType::ENEMY_BULLET);
	coliisionCpnt->m_onCollisionFunc = bind(&onCollision, actor, std::placeholders::_1);

	return actor;
}

void GameActor::update(float _deltaTime) {
	caluculateWorldTransform();

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
				cpnt->update(_deltaTime);
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
				gac->update(_deltaTime);
			}
		}
	}
}

void GameActor::input(float _deltaTime)
{
	//自分のコンポーネントの入力処理
	if (!m_componentList.empty()) {
		for (const auto& cpnt : m_componentList) {
			if (cpnt->GetComponentState() == Component::ComponentState::EActive) {
				cpnt->input(_deltaTime);
			}
		}
	}
	//子ゲームアクターの入力処理
	if (!m_childList.empty()) {
		for (auto& gac : m_childList) {
			if (gac->GetActorState() == ActorState::EActive) {
				gac->input(_deltaTime);
			}
		}
	}
}


void GameActor::draw()
{
	if (GetActorDrawState() == ActorDrawState::EVisible) {
		ofPushMatrix();
		ofTranslate(this->m_worldPos);
		ofRotateDeg(-(this->m_worldRotAngle));
		ofScale(this->m_worldScale);

		assert(this->drawfunc != nullptr);
		this->drawfunc();
		ofPopMatrix();
	}

	if (!m_childList.empty()) {
		for (auto& gac : m_childList) {
			gac->draw();
		}
	}

}

void GameActor::onCollision(CollisionComponent* _other)
{
	drawfunc = [=]() {
		ofSetColor(ofColor::pink);
		//ofDrawRectangle(ofVec3f(0, 0), 30, 30);
		ofDrawRectangle(ofVec3f(-15, -15), 30, 30);
	};
}

GameActor* GameActor::addChild()
{
	auto actor = make_unique<GameActor>();
	auto res = actor.get();
	m_childAddQue.push(move(actor));
	res->mp_parent = this;
	return res;
}

void GameActor::RemoveAllChild()
{
	queue<unique_ptr<GameActor>>().swap(m_childAddQue);	//queueの全消し
	for (auto& gac : m_childList) {
		gac->StateErace();
	}
}
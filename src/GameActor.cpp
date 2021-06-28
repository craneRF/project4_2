#include "ofApp.h"
#include "GameActor.h"
#include "stdComponent.h"

GameActor::GameActor(string _name) 
	:Actor(_name)
	, mp_parent(nullptr)
{
	m_componentList.clear();
	m_childList.clear();
}

GameActor::~GameActor()
{
}

void GameActor::caluculateWorldTransform() {
	if (mp_parent != nullptr) {
		m_worldScale = mp_parent->m_worldScale * m_scale;
		m_worldRotAngle = mp_parent->m_worldRotAngle + m_rotAngle;
		m_worldPos = mp_parent->m_worldPos +
			m_pos.getRotated(-mp_parent->m_worldRotAngle, ofVec3f(0, 0, 1)) *
			mp_parent->m_worldScale;
	}
	else {
		Actor::caluculateWorldTransform();
	}
}

GameActor* GameActor::createPlayer(GameActor* _parent, ofVec3f _pos, string _name)
{
	auto actor = _parent->addChild();
	actor->initialize(_pos, _name);
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
	actor->initialize(_pos, _name);
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

	//ofApp::getInstance()->hierarchyRoot_->RotAngle() += 1.f;

	/*if (mp_parent) {
		m_rotAngle++;
		if (m_rotAngle > 360)
		{
			m_rotAngle = 0.f;
		}
	}*/
	m_componentList.erase(
		remove_if(m_componentList.begin(), m_componentList.end(),
			[](const auto& cpnt) { return cpnt->GetComponentState() == Component::ComponentState::EErace; }),
		m_componentList.end()
	);
	//�����̃R���|�[�l���g�̍X�V����
	for (const auto& cpnt : m_componentList) {
		if (cpnt->GetComponentState() != Component::ComponentState::EPause) {
			cpnt->update(_deltaTime);
		}
	}
	//DrawOrder
	//ofApp::getInstance()->draworderset_.insert(this);
	//�폜�\��A�N�^�[�̍폜
	m_childList.erase(
		remove_if(m_childList.begin(), m_childList.end(),
			[](const auto& gac) { return gac->GetActorState() == ActorState::EErace; }),
		m_childList.end()
	);
	//�ǉ��҂��A�N�^�[�̒ǉ�����
	while (!m_childAddQue.empty()) {
		m_childList.push_back(move(m_childAddQue.front()));
		m_childAddQue.pop();
	}
	//�q�Q�[���A�N�^�[�̑S������
	for (auto& gac : m_childList) {
		if (gac->GetActorState() != ActorState::EPause) {
			gac->update(_deltaTime);
		}
	}
}

void GameActor::input(float _deltaTime)
{
	for (auto& gac : m_childList) {
		if (gac->GetActorState() == ActorState::EActive) {
			gac->update(_deltaTime);
		}
	}
}


void GameActor::draw(float _deltaTime)
{
	Actor::draw();

	for (auto& gac : m_childList) {
		gac->draw(_deltaTime);
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
	queue<unique_ptr<GameActor>>().swap(m_childAddQue);	//queue�̑S����
	for (auto& gac : m_childList) {
		gac->StateErace();
	}
}
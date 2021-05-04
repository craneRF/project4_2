#include "GameActor.h"
#include "ofApp.h"
#include "stdComponent.h"

GameActor::GameActor(string _name) :
	m_pos(ofVec3f(0, 0, 0))
	, m_scale({ 1,1,1 })
	, drawfunc([]() {})
{

}

GameActor::~GameActor()
{
}

ofVec3f& GameActor::Pos() {
	return m_pos;
}

const ofVec3f& GameActor::WorldPos() {
	return m_worldPos;
}

float& GameActor::RotAngle() {
	return m_rotAngle;
}

ofVec3f& GameActor::Scale() {
	return m_scale;
}

string& GameActor::Name() {
	return m_name;
}

void GameActor::caluculateWorldTransform() {
	if (m_parent != nullptr) {
		m_worldScale = m_parent->m_worldScale * m_scale;
		m_worldRotAngle = m_parent->m_worldRotAngle + m_rotAngle;
		m_worldPos = m_parent->m_worldPos +
			m_pos.getRotated(-m_parent->m_worldRotAngle, ofVec3f(0, 0, 1)) *
			m_parent->m_worldScale;
	}
	else {
		m_worldScale = m_scale;
		m_worldRotAngle = m_rotAngle;
		m_worldPos = m_pos.getRotated(-m_rotAngle, ofVec3f(0, 0, 1)) * m_scale;
	}
}

void GameActor::initialize(ofVec3f _pos, string _name) {
	m_pos = _pos;
	caluculateWorldTransform();
	m_name = _name;
}

GameActor* GameActor::addChild()
{
	auto actor = make_unique<GameActor>();
	auto res = actor.get();
	m_childAddQue.push(move(actor));
	res->m_parent = this;
	return res;
}

void GameActor::createPlayer(GameActor* _parent, ofVec3f _pos, string _name)
{
	auto actor = _parent->addChild();
	actor->initialize(_pos, _name);
	//auto moveCpnt = actor->addComponent<MoveComponent>();
	actor->drawfunc = [=]() {
		ofSetColor(ofColor::green);
		ofDrawRectangle(actor->Pos(), 30, 30);
	};

}

void GameActor::update() {
	caluculateWorldTransform();

	//自分のコンポーネントの更新処理
	for (const auto& c : mp_componentList) {
		c->update();
	}
	//DrawOrder
	//ofApp::getInstance()->draworderset_.insert(this);
	//削除予定アクターの削除
	m_childList.erase(
		remove_if(m_childList.begin(), m_childList.end(),
			[](const auto& a) {return a->waitforErase_; }),
		m_childList.end()
	);
	//追加待ちアクターの追加処理
	while (!m_childAddQue.empty()) {
		m_childList.push_back(move(m_childAddQue.front()));
		m_childAddQue.pop();
	}
	//子ゲームアクターの全件処理
	for (auto& c : m_childList) {
		c->update();
	}
}


void GameActor::draw()
{
	ofPushMatrix();
	//ofTranslate(m_pos);
	//ofRotateDeg(-m_rotAngle);
	//ofScale(m_scale);
	ofTranslate(m_worldPos);
	ofRotateDeg(-m_worldRotAngle);
	ofScale(m_worldScale);

	assert(drawfunc != nullptr);
	drawfunc();
	for (auto& c : m_childList) {
		c->draw();
	}

	ofPopMatrix();
}

#include "ofApp.h"
#include "GameActor.h"
#include "stdComponent.h"

GameActor::GameActor(string _name) :
	m_pos(ofVec3f(0, 0, 0))
	, m_rotAngle(0)
	, m_worldRotAngle(0)
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

const float & GameActor::WorldRotAngle()
{
	return m_worldRotAngle;
}

ofVec3f& GameActor::Scale() {
	return m_scale;
}

const ofVec3f & GameActor::WorldScale()
{
	return m_worldScale;
}

void GameActor::setParam(ofVec3f _pos, ofVec3f _scale, float _angle)
{
	Pos() = _pos;
	Scale() = _scale;
	RotAngle() = _angle;
}

string& GameActor::Name() {
	return m_name;
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
		m_worldScale = m_scale * ((float)ofGetHeight() / (float)Define::FULLWIN_H);
		m_worldRotAngle = m_rotAngle;
		m_worldPos = m_pos.getRotated(-m_rotAngle, ofVec3f(0, 0, 1)) * m_scale* ((float)ofGetHeight() / (float)Define::FULLWIN_H);
	}
}

void GameActor::initialize(ofVec3f _pos, string _name) {
	m_pos = _pos;
	caluculateWorldTransform();
	m_name = _name;
}

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

void GameActor::update(float _deltatime) {
	caluculateWorldTransform();

	//ofApp::getInstance()->hierarchyRoot_->RotAngle() += 1.f;

	//�����̃R���|�[�l���g�̍X�V����
	for (const auto& c : mp_componentList) {
		c->update(_deltatime);
	}
	//DrawOrder
	//ofApp::getInstance()->draworderset_.insert(this);
	//�폜�\��A�N�^�[�̍폜
	m_childList.erase(
		remove_if(m_childList.begin(), m_childList.end(),
			[](const auto& a) {return a->waitforErase_; }),
		m_childList.end()
	);
	//�ǉ��҂��A�N�^�[�̒ǉ�����
	while (!m_childAddQue.empty()) {
		m_childList.push_back(move(m_childAddQue.front()));
		m_childAddQue.pop();
	}
	//�q�Q�[���A�N�^�[�̑S������
	for (auto& c : m_childList) {
		c->update(_deltatime);
	}
}

void GameActor::draw(float _deltatime)
{
	ofPushMatrix();
	ofTranslate(m_worldPos);
	ofRotateDeg(-m_worldRotAngle);
	ofScale(m_worldScale);

	assert(drawfunc != nullptr);
	drawfunc();
	ofPopMatrix();

	for (auto& c : m_childList) {
		c->draw(_deltatime);
	}

}

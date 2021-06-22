#include "UIActor.h"

UIActor::UIActor(string _name)
	:Actor(_name)
	/*m_pos(ofVec3f(0, 0, 0))
	, m_rotAngle(0)
	, m_worldRotAngle(0)
	, m_scale({ 1,1,1 })
	, drawfunc([]() {})*/
{
}

UIActor::~UIActor()
{
}

//void UIActor::setParam(ofVec3f _pos, ofVec3f _scale, float _angle)
//{
//	Pos() = _pos;
//	Scale() = _scale;
//	RotAngle() = _angle;
//} 

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

//void UIActor::initialize(ofVec3f _pos, string _name)
//{
//	m_pos = _pos;
//	caluculateWorldTransform();
//	m_name = _name;
//}

void UIActor::update(float _deltaTime)
{
	caluculateWorldTransform();

	//�폜�\��UI�A�N�^�[�̍폜
	m_UIchildList.erase(
		remove_if(m_UIchildList.begin(), m_UIchildList.end(),
			[](const auto& a) {return a->GetUIActorState() == UIActor::UIActorState::EClosing; }),
		m_UIchildList.end()
	);

	//�ǉ��҂�UI�A�N�^�[�̒ǉ�����
	while (!m_UIchildAddQue.empty()) {
		m_UIchildList.push_back(move(m_UIchildAddQue.front()));
		m_UIchildAddQue.pop();
	}
	//�qUI�A�N�^�[�̑S������
	for (auto& uiac : m_UIchildList)
	{
		if (uiac->GetUIActorState() != UIActor::UIActorState::EDrew && uiac->GetUIActorState() != UIActor::UIActorState::EClosing) {
			if (uiac->GetUIActorState() == UIActor::UIActorState::EActive) {
				uiac->input(_deltaTime);  //���쏈����EActive��Ԃ�UIScreen�����s��Ȃ�
			}
			uiac->update(_deltaTime);  //�`��ɉe�����鏈���Ȃǂ�EActive��Ԃ�EDrawing��Ԃ̎��ɍs��
		}
	}
}

void UIActor::input(float _deltaTime)
{
}

void UIActor::draw(float _deltaTime)
{
	/*ofPushMatrix();
	ofTranslate(m_worldPos);
	ofRotateDeg(-m_worldRotAngle);
	ofScale(m_worldScale);

	assert(drawfunc != nullptr);
	drawfunc();
	ofPopMatrix();*/

	Actor::draw();

	for (auto& c : m_UIchildList) {
		c->draw(_deltaTime);
	}

}

void UIActor::Close()
{
}

UIActor * UIActor::addUIChild()
{
	auto actor = make_unique<UIActor>();
	auto res = actor.get();
	m_UIchildAddQue.push(move(actor));
	res->mp_UIparent = this;
	return res;
}

void UIActor::RemoveAllChild()
{
	queue<unique_ptr<UIActor>>().swap(m_UIchildAddQue);	//queue�̑S����
	for (auto& c : m_UIchildList) {
		c->Close();
	}
}

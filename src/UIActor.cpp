//#include "UIActor.h"
//
//UIActor::UIActor(string _name)
//	:Actor(_name)
//	, mp_UIparent(nullptr)
//{
//	mp_fontRenderer = make_unique<FontRenderer>();
//	mp_TexRenderer = make_unique<TextureRenderer>();
//}
//
//UIActor::~UIActor()
//{
//}
//
//void UIActor::update(float _deltaTime)
//{
//	////�폜�\��UI�A�N�^�[�̍폜
//	//m_UIchildList.erase(
//	//	remove_if(m_UIchildList.begin(), m_UIchildList.end(),
//	//		[](const auto& uic) {return uic->GetActorState() == ActorState::EErace; }),
//	//	m_UIchildList.end()
//	//);
//
//	////�ǉ��҂�UI�A�N�^�[�̒ǉ�����
//	//while (!m_UIchildAddQue.empty()) {
//	//	m_UIchildList.push_back(move(m_UIchildAddQue.front()));
//	//	m_UIchildAddQue.pop();
//	//}
//	////�qUI�A�N�^�[�̑S������
//	//for (auto& uic : m_UIchildList)
//	//{
//	//	if (uic->GetActorState() != ActorState::EPause) {
//	//		uic->update(_deltaTime);  //�`��ɉe�����鏈���Ȃǂ�EActive��Ԃ�EDrawing��Ԃ̎��ɍs��
//	//	}
//	//}
//}
//
//void UIActor::input(float _deltaTime)
//{
//	//for (auto& uic : m_UIchildList)
//	//{
//	//	if (uic->GetActorState() == ActorState::EActive) {
//	//		uic->input(_deltaTime);  //���쏈����EActive��Ԃ�UIScreen�����s��Ȃ�
//	//	}
//	//}
//}
//
//void UIActor::draw()
//{
//	/*for (auto& uic : m_UIchildList) {
//		if (uic->GetActorDrawState() == ActorDrawState::EVisible) {
//			uic->draw();
//		}
//	}*/
//}
//
//void UIActor::RemoveAllChild()
//{
//	//queue<unique_ptr<UIActor>>().swap(m_UIchildAddQue);	//queue�̑S����
//	//for (auto& uic : m_UIchildList) {
//	//	uic->StateErace();
//	//}
//}

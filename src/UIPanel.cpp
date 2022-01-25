//#include "ofApp.h"
//#include "UIPanel.h"
//
//UIPanel::UIPanel(string _name)
//	:Actor(_name)
//	,mp_UIPanelParent(nullptr)
//	,mp_UICanvasParent(nullptr)
//{
//	m_UICommonChildList.clear();
//	m_UIPanelChildList.clear();
//}
//
//UIPanel::~UIPanel()
//{
//}
//
//void UIPanel::caluculateWorldTransform()
//{
//	if (this->RotAngle() >= 360.0f) {
//		this->RotAngle() = 0.0f;
//	}
//
//	if (mp_UIPanelParent != nullptr) {
//		this->WorldScale() = mp_UIPanelParent->WorldScale() * this->Scale();
//		this->WorldRotAngle() = mp_UIPanelParent->WorldRotAngle() + this->RotAngle();
//		this->WorldPos() = mp_UIPanelParent->WorldPos() +
//			this->Pos().getRotated(-(mp_UIPanelParent->WorldRotAngle()), ofVec3f(0, 0, 1)) *
//			mp_UIPanelParent->WorldScale();
//	}
//	else {
//		this->WorldScale() = this->Scale()* ((float)ofGetHeight() / (float)Define::FULLWIN_H);
// 		this->WorldRotAngle() = this->RotAngle();
//		this->WorldPos() = this->Pos().getRotated(-(this->RotAngle()), ofVec3f(0, 0, 1)) * this->Scale()* ((float)ofGetHeight() / (float)Define::FULLWIN_H);
//	}
//}
//
//void UIPanel::update()
//{
//	caluculateWorldTransform();
//	m_actorDelta = ofApp::getInstance()->m_deltaTime;
//
//	//íœ—\’èUICommon‚Ìíœ
//	if (!m_UICommonChildList.empty()) {
//		m_UICommonChildList.erase(
//			remove_if(m_UICommonChildList.begin(), m_UICommonChildList.end(),
//				[](const auto& uic) {return uic->GetActorState() == ActorState::EErace; }),
//			m_UICommonChildList.end()
//		);
//	}
//
//	//’Ç‰Á‘Ò‚¿UICommon‚Ì’Ç‰Áˆ—
//	while (!m_UICommonChildAddQue.empty()) {
//		m_UICommonChildList.push_back(move(m_UICommonChildAddQue.front()));
//		m_UICommonChildAddQue.pop();
//	}
//	//ŽqUICommon‚Ì‘SŒˆ—
//	if (!m_UICommonChildList.empty()) {
//		for (auto& uic : m_UICommonChildList)
//		{
//			if (uic->GetActorState() != ActorState::EPause) {
//				for (auto& uf : uic->UIupdatefuncVec) {
//					assert(uf != nullptr);
//					uf();
//				}
//				//uic->update();  //•`‰æ‚É‰e‹¿‚·‚éˆ—‚È‚Ç‚ÍEActiveó‘Ô‚ÆEDrawingó‘Ô‚ÌŽž‚És‚¤
//			}
//		}
//	}
//
//	//íœ—\’èUIPanel‚Ìíœ
//	if (!m_UIPanelChildList.empty()) {
//		m_UIPanelChildList.erase(
//			remove_if(m_UIPanelChildList.begin(), m_UIPanelChildList.end(),
//				[](const auto& uic) {return uic->GetActorState() == ActorState::EErace; }),
//			m_UIPanelChildList.end()
//		);
//	}
//
//	//’Ç‰Á‘Ò‚¿UIPanel‚Ì’Ç‰Áˆ—
//	while (!m_UIPanelChildAddQue.empty()) {
//		m_UIPanelChildList.push_back(move(m_UIPanelChildAddQue.front()));
//		m_UIPanelChildAddQue.pop();
//	}
//	//ŽqUIPanel‚Ì‘SŒˆ—
//	if (!m_UIPanelChildList.empty()) {
//		for (auto& uic : m_UIPanelChildList)
//		{
//			if (uic->GetActorState() != ActorState::EPause) {
//				/*for (auto& uipcu : UIupdatefuncVec) {
//					uipcu();
//				}*/
//				uic->update();  //•`‰æ‚É‰e‹¿‚·‚éˆ—‚È‚Ç‚ÍEActiveó‘Ô‚ÆEDrawingó‘Ô‚ÌŽž‚És‚¤
//			}
//		}
//	}
//}
//
//void UIPanel::input()
//{
//	if (!m_UICommonChildList.empty()) {
//		for (auto& uic : m_UICommonChildList)
//		{
//			if (uic->GetActorState() == ActorState::EActive) {
//				uic->input();  //‘€ìˆ—‚ÍEActiveó‘Ô‚ÌUIScreen‚µ‚©s‚í‚È‚¢
//			}
//		}
//	}
//
//	if (!m_UIPanelChildList.empty()) {
//		for (auto& uic : m_UIPanelChildList)
//		{
//			if (uic->GetActorState() == ActorState::EActive) {
//				uic->input();  //‘€ìˆ—‚ÍEActiveó‘Ô‚ÌUIScreen‚µ‚©s‚í‚È‚¢
//			}
//		}
//	}
//}
//
//void UIPanel::draw()
//{
//	if (!m_UICommonChildList.empty()) {
//		for (auto& uic : m_UICommonChildList) {
//			if (uic->GetActorDrawState() == ActorDrawState::EVisible) {
//				for (auto& df : uic->UIdrawfuncVec) {
//					assert(df != nullptr);
//					ofPushMatrix();
//					ofTranslate(uic->WorldPos());
//					ofRotateDeg(-(uic->WorldRotAngle()));
//					ofScale(uic->WorldScale());
//
//					df();
//					ofPopMatrix();
//				}
//				//uic->draw();
//				/*assert(uic->UIdrawfunc != nullptr);
//				uic->UIdrawfunc();*/
//			}
//		}
//	}
//
//	if (!m_UIPanelChildList.empty()) {
//		for (auto& uic : m_UIPanelChildList) {
//			if (uic->GetActorDrawState() == ActorDrawState::EVisible) {
//				uic->draw();
//			}
//		}
//	}
//}
//
//void UIPanel::RemoveAllChild()
//{
//	queue<unique_ptr<UICommon>>().swap(m_UICommonChildAddQue);	//queue‚Ì‘SÁ‚µ
//	for (auto& uic : m_UICommonChildList) {
//		uic->StateErace();
//	}
//
//	queue<unique_ptr<UIPanel>>().swap(m_UIPanelChildAddQue);	//queue‚Ì‘SÁ‚µ
//	for (auto& uic : m_UIPanelChildList) {
//		uic->StateErace();
//	}
//}
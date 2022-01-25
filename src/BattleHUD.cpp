//#include "ofApp.h"
//#include "BattleHUD.h"
//#include "UIStandardPanel.h"
//#include "UISprite.h"
//#include "UIFont.h"
//
//BattleHUD::BattleHUD()
//	:UICanvas("BattleHUD")
//{
//	buttonPanel = addUIPanel<UIStandardPanel>("ButtonPanel");
//	buttonPanel->Pos() = { static_cast<float>(Define::FULLWIN_W / 2), static_cast<float>(Define::FULLWIN_H / 2) };
//
//
//	button01 = buttonPanel->addUIPanel<UIStandardPanel>("Button01");
//
//	button01Sprite = button01->addUICommon<UISprite>("Button01");
//	//button01Sprite->AlignPivotCenter();
//	button01Sprite->initialize("button1.png", { 0, 0, 0 }, {0.2f, 0.2f});
//
//	button01Font = button01->addUICommon<UIFont>("Button01");
//	button01Font->initialize(u8"UŒ‚", 18);
//	button01Font->Scale() = { 2.0f, 2.0f, 1.0f };
//
//
//	button02 = buttonPanel->addUIPanel<UIStandardPanel>("Button02");
//	button02->Pos() += {0.0f, 100.0f};
//
//	button02Sprite = button02->addUICommon<UISprite>("Button02");
//	//button02Sprite->AlignPivotCenter();
//	button02Sprite->initialize("button1.png", { 0, 0, 0 }, { 0.2f, 0.2f });
//
//	button02Font = button02->addUICommon<UIFont>("Button02");
//	button02Font->initialize(u8"UŒ‚", 18);
//	button02Font->Scale() = { 2.0f, 2.0f, 1.0f };
//
//	//button02Sprite->UIupdatefunc = [&]() {button02Sprite->Pos() += {1.0f, 1.0f}; };
//
//	/*button02Sprite->UIupdatefuncVec.emplace_back([&]() {
//			button02Sprite->Pos() += {1.0f, 1.0f};
//		}
//	);*/
//
//	/*uif = addUICommon<UIFont>("Font");
//	uif->initialize("BattleHUD", 18, { 150.0f, 150.0f, 0.0f }, ofColor::white, {2.0f, 2.0f, 1.0f});*/
//
//	/*uis2 = addUICommon<UISprite>("Sprite2");
//	uis2->initialize("marine_icon.png", { 150.0f, 150.0f, 0.0f }, { 0.025f,0.025f }, 0.0f);*/
//
//	//uis2->UIupdatefunc = [&]() { uis2->Pos() += {1.0f, 1.0f}; };
//	//uis2->UIupdatefuncVec.push_back([&]() { uis2->Pos() += {1.0f, 1.0f}; });
//
//	/*uis2->UIinputfunc = [&]() { 
//		if (ofApp::getInstance()->mp_inputManager->getButtonHold("Bomb")) {
//			uis2->Pos() += {1.0f, 0.0f};
//		}
//	};*/
//	//uis2->UIupdatefunc();
//	//uis2->UIupdatefuncVec.push_back([=](){ uis2->Pos() = uis2->Pos() + 1.0f; });
//	/*uif2 = addUICommon<UIFont>("Font2");
//	uif2->initialize("Font", 18, { 150.0f, 150.0f, 0.0f }, ofColor::white, { 2.0f, 2.0f, 1.0f });*/
//	/*uis = addUICommon<UISprite>("Sprite");
//	uis->initialize("marine_icon.png", { 100.0f, 100.0f, 0.0f }, { 0.025f, 0.025f }, 0.0f);*/
//}
//
//BattleHUD::~BattleHUD()
//{
//}
//
////void BattleHUD::update()
////{
////	UIPanelCanvas::update();
////}
////
////void BattleHUD::input()
////{
////	UIPanelCanvas::input();
////}
////
////void BattleHUD::draw()
////{
////	UIPanelCanvas::draw();
////}

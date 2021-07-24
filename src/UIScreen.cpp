#include "ofApp.h"
#include "UIScreen.h"
#include "UISprite.h"
#include "UIPanelCanvas.h"

UIScreen::UIScreen(string _screenName, UIPanelCanvas* _canvas)
	:m_screenName(_screenName)
	,m_UIScreenState(UIScreenState::EActive)
	,m_UIScreenDrawState(UIScreenDrawState::EVisible)
	,mp_Canvas(_canvas)
{
}

UIScreen::~UIScreen()
{
}

void UIScreen::initialize()
{
}

void UIScreen::update(float _deltaTime)
{
	mp_Canvas->update(_deltaTime);
}

void UIScreen::input(float _deltaTime)
{
	mp_Canvas->input(_deltaTime);
}

void UIScreen::draw()
{
	mp_Canvas->draw();
}

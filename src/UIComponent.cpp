#include "GameActor.h"
#include "UIComponent.h"

UIComponent::UIComponent(GameActor * _gactor)
	: Component(_gactor, "UIComponent")
	, mp_UICanvasParent(nullptr)
{
	gActor()->Def() = GameActor::Definition::UI;
	gActor()->addTag("UIComponent");
}

UIComponent::~UIComponent()
{
}

void UIComponent::update()
{
	for (auto & uuv : UIupdatefuncVec) {
		uuv();
	}
}

void UIComponent::input()
{
	for (auto & uiv : UIinputfuncVec) {
		uiv();
	}
}

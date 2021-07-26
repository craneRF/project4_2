#pragma once
#include "UIActor.h"
#include "Renderer.h"

class UIPanel;

class UICommon : public Actor
{
protected:
	unique_ptr<FontRenderer> mp_fontRenderer;
	unique_ptr<TextureRenderer> mp_TexRenderer;
public:
	UICommon(string _name = "");
	virtual ~UICommon() = 0;

	void caluculateWorldTransform();

	virtual void update(float _deltaTime) = 0;
	virtual void input(float _deltaTime) = 0;
	virtual void draw() = 0;

	UIPanel* mp_UIPanelParent;  //自身がどのUIPanelに存在しているのかを格納する変数。(UIScreenが削除されるとUIActorも削除される)

	function<void(float)> UIupdatefunc;
	function<void(float)> UIinputfunc;
	function<void()> UIdrawfunc;
};


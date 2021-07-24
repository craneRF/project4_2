#include "UIPanelCanvas.h"

UIPanelCanvas::UIPanelCanvas(string _name)
	:UIPanel(_name)
{
}

UIPanelCanvas::~UIPanelCanvas()
{
}

void UIPanelCanvas::update(float _deltatime)
{
	UIPanel::update(_deltatime);
}

void UIPanelCanvas::input(float _deltatime)
{
	UIPanel::input(_deltatime);
}

void UIPanelCanvas::draw()
{
	UIPanel::draw();
}

#pragma once
#include "ofMain.h"
#include "Component.h"

class GameActor;

class FontRendererComponent :
	public Component
{
private:
	ofTrueTypeFont m_font;
	ofColor m_col;
	string m_str;
	ofVec3f m_offset;

public:
	FontRendererComponent(GameActor* _gactor);
	virtual ~FontRendererComponent();
	void initialize(ofTrueTypeFont _font, string _str, ofVec3f _offset = { 0,0,0 }, ofColor _col = ofColor::black);
	virtual void update();
	virtual void draw();
	string& String();
	ofColor& Color();
};
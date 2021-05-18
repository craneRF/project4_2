#include "FontRendererComponent.h"
#include "GameActor.h"

FontRendererComponent::FontRendererComponent(GameActor* _gactor) :
	Component(_gactor, "FontRendererComponent"), m_str(""), m_col(ofColor::black)
{
}

FontRendererComponent::~FontRendererComponent()
{
}

void FontRendererComponent::initialize(ofTrueTypeFont _font, string _str, ofVec3f _offset, ofColor _col)
{
	m_offset = _offset;
	m_font = _font;
	m_str = _str;
	m_col = _col;
	mp_gActor->drawfunc = std::bind(&FontRendererComponent::draw, this);
}

void FontRendererComponent::update(float _deltatime)
{
}

void FontRendererComponent::draw()
{
	ofTranslate(m_offset);
	ofSetColor(m_col);
	m_font.drawString(m_str, 0, 0);
}

string& FontRendererComponent::String()
{
	return m_str;
}

ofColor& FontRendererComponent::Color()
{
	return m_col;
}

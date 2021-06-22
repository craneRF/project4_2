#include "ofApp.h"
#include "FontRendererComponent.h"
#include "GameActor.h"

FontRendererComponent::FontRendererComponent(GameActor* _gactor) 
	:Component(_gactor, "FontRendererComponent")
	, m_size(0)
	, m_fontName("")
	, m_sizeBuffer(m_size)
	, m_fontNameBuffer(m_fontNameBuffer)
{
	mp_fontRenderer = make_unique<FontRenderer>();
}

FontRendererComponent::~FontRendererComponent()
{
}

void FontRendererComponent::initialize(const string & _str, int _size, ofVec3f _offset, ofColor _col, ofVec3f _scale, const string & _fontname)
{
	String() = _str;
	Offset() = _offset;
	Color() = _col;
	Scale() = _scale;

	m_size = _size;
	m_fontName = _fontname;

	mp_fontRenderer->SetSize(m_size);
	mp_fontRenderer->SetFontName(m_fontName);

	m_sizeBuffer = m_size;
	m_fontNameBuffer = m_fontName;

	mp_gActor->drawfunc = std::bind(&FontRendererComponent::draw, this);
}

void FontRendererComponent::update(float _deltatime)
{
	if (m_sizeBuffer != m_size) {
		mp_fontRenderer->SetSize(m_size);
		m_sizeBuffer = m_size;
	}
	if (m_fontNameBuffer != m_fontName) {
		mp_fontRenderer->SetFontName(m_fontName);
		m_fontNameBuffer = m_fontName;
	}
}

void FontRendererComponent::draw()
{
	mp_fontRenderer->FontDraw();
}
#include "ofApp.h"
#include "FontRendererComponent.h"
#include "GameActor.h"

FontRendererComponent::FontRendererComponent(GameActor* _gactor) 
	:Component(_gactor, "FontRendererComponent")
	, m_str("Not String")
	, m_size(18)
	, m_offset({ 0,0,0 })
	, m_col(ofColor::white)
	, m_scale({ 1, 1, 1 })
	, m_fontName("keifont.ttf")
	, m_sizeBuffer(m_size)
	, m_fontNameBuffer(m_fontName)
{
	mp_fontRenderer = make_unique<FontRenderer>();
	//mp_gActor->drawfunc = std::bind(&FontRendererComponent::draw, this);
	mp_gActor->drawfuncVec.emplace_back(std::bind(&FontRendererComponent::draw, this));
}

FontRendererComponent::~FontRendererComponent()
{
}

void FontRendererComponent::initialize(const string & _str, int _size, ofVec3f _offset, ofColor _col, ofVec3f _scale, const string & _fontname)
{
	m_str = _str;
	m_offset = _offset;
	m_col = _col;
	m_scale = _scale;

	m_size = _size;
	m_fontName = _fontname;

	mp_fontRenderer->SetSize(m_size);
	mp_fontRenderer->SetFontName(m_fontName);

	m_sizeBuffer = m_size;
	m_fontNameBuffer = m_fontName;
}

void FontRendererComponent::update()
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

void FontRendererComponent::input()
{
}

void FontRendererComponent::draw()
{
	if (m_CpntDrawState == Component::ComponentDrawState::EVisible) {
		mp_fontRenderer->FontDraw(m_str, m_offset, m_col, m_scale);
	}
}

void FontRendererComponent::AlignPivotCenter()
{
	auto fontPtr = ofApp::getInstance()->mp_font->GetFontMap().begin()->second.begin()->second;
	m_offset = { fontPtr->stringWidth(m_str) * -0.5f * m_scale.x,fontPtr->stringHeight(m_str) * 0.25f * m_scale.y };
}

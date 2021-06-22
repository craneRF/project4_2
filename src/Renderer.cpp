#include "Renderer.h"

FontRenderer::FontRenderer()
	:m_str("Not String")
	,m_size(18)
	,m_offset(ofVec3f{ 0, 0, 0 })
	,m_col(ofColor::white)
	,m_scale(ofVec3f{ 1, 1, 1 })
	,m_fontName("keifont.ttf")
	,mp_currentFont(nullptr)
{
	mp_currentFont = make_shared<ofTrueTypeFont>();
	mp_currentFont = ofApp::getInstance()->mp_font->GetFontMap().find(m_fontName)->second.find(m_size)->second;
}

FontRenderer::~FontRenderer()
{
}

void FontRenderer::FontDraw()
{
	ofTranslate(m_offset);
	ofSetColor(m_col);
	ofScale(m_scale);
	mp_currentFont->drawString(m_str, 0, 0);
}


//--------------------------------------------------------------
TextureRenderer::TextureRenderer()
	:m_offset(ofVec3f{ 0, 0, 0 })
	,m_col(ofColor::white)
	,m_scale(ofVec3f{ 1, 1, 1 })
	,m_texName("")
{
}

TextureRenderer::~TextureRenderer()
{
}

void TextureRenderer::TextureDraw()
{
	ofSetColor(m_col);
	ofScale(m_scale);
	mp_image->draw(m_offset);
}

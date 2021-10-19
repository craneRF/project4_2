#include "Renderer.h"
#include "ofApp.h"

FontRenderer::FontRenderer()
	:m_size(18)
	,m_fontName("keifont.ttf")
	,mp_currentFont(nullptr)
{
	mp_currentFont = make_shared<ofTrueTypeFont>();
	mp_currentFont = ofApp::getInstance()->mp_font->GetFontMap().find(m_fontName)->second.find(m_size)->second;
}

FontRenderer::~FontRenderer()
{
}

void FontRenderer::SetSize(int _size)
{
	m_size = _size;
	mp_currentFont = ofApp::getInstance()->mp_font->GetFontMap().find(m_fontName)->second.find(m_size)->second;
}

void FontRenderer::SetFontName(const string & _fontname)
{
	m_fontName = _fontname;
	mp_currentFont = ofApp::getInstance()->mp_font->GetFontMap().find(m_fontName)->second.find(m_size)->second;
}

void FontRenderer::FontDraw(string _str, ofVec3f _offset, ofColor _col, ofVec3f _scale)
{
	ofTranslate(_offset);
	ofSetColor(_col);
	ofScale(_scale);
	mp_currentFont->drawString(_str, 0, 0);
}

//--------------------------------------------------------------
TextureRenderer::TextureRenderer()
{
}

TextureRenderer::~TextureRenderer()
{
}

void TextureRenderer::SetTexture(const string & _texname)
{
	mp_image = ofApp::getInstance()->mp_texture->GetImage("images/" + _texname);
}

void TextureRenderer::TextureDraw(ofVec3f _offset, ofColor _col, ofVec3f _scale, float _degree)
{
	ofTranslate(_offset);
	ofSetColor(_col);
	ofRotateDeg(-(_degree));
	ofScale(_scale);
	mp_image->draw({ 0,0 });
}

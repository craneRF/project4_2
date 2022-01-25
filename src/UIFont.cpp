//#include "ofApp.h"
//#include "UIFont.h"
//#include "GameActor.h"
//
//UIFont::UIFont(string _name)
//	:UICommon(_name)
//	, m_str("Not String")
//	, m_size(18)
//	, m_offset({ 0,0,0 })
//	, m_col(ofColor::white)
//	, m_scale({ 1, 1, 1 })
//	, m_fontName("keifont.ttf")
//	, m_sizeBuffer(m_size)
//	, m_fontNameBuffer(m_fontName)
//{
//	//UIupdatefunc = std::bind(&UIFont::update, this);
//	UIupdatefuncVec.emplace_back(bind(&UIFont::update, this));
//	//UIdrawfunc = std::bind(&UIFont::draw, this);
//	UIdrawfuncVec.emplace_back(bind(&UIFont::draw, this));
//}
//
//UIFont::~UIFont()
//{
//}
//
//void UIFont::initialize(const string & _str, int _size, ofVec3f _offset, ofColor _col, ofVec3f _scale, const string & _fontname)
//{
//	m_str = _str;
//	m_offset = _offset;
//	m_col = _col;
//	m_scale = _scale;
//
//	m_size = _size;
//	m_fontName = _fontname;
//
//	mp_fontRenderer->SetSize(m_size);
//	mp_fontRenderer->SetFontName(m_fontName);
//
//	m_sizeBuffer = m_size;
//	m_fontNameBuffer = m_fontName;
//}
//
//void UIFont::update()
//{
//	if (m_sizeBuffer != m_size) {
//		mp_fontRenderer->SetSize(m_size);
//		m_sizeBuffer = m_size;
//	}
//	if (m_fontNameBuffer != m_fontName) {
//		mp_fontRenderer->SetFontName(m_fontName);
//		m_fontNameBuffer = m_fontName;
//	}
//}
//
//void UIFont::input()
//{
//}
//
//void UIFont::draw()
//{
//	mp_fontRenderer->FontDraw(m_str, m_offset, m_col, m_scale);
//}
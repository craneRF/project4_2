#include "UISprite.h"

UISprite::UISprite(string _name)
	:UICommon(_name)
	,m_offset({ 0.0f, 0.0f, 0.0f })
	,m_col(ofColor::white)
	,m_scale({ 1.0f, 1.0f, 1.0f })
	,m_texName("NoSearch.png")
	,m_texNameBuffer(m_texName)
{
	mp_TexRenderer->SetTexture(m_texName);

	UIupdatefunc = bind(&UISprite::update, this);
	UIdrawfunc = bind(&UISprite::draw, this);
}

UISprite::~UISprite()
{
}

void UISprite::initialize(const string& _texname, ofVec3f _offset, ofVec3f _scale, float _degree, ofColor _col)
{
	m_offset = _offset;
	m_scale = _scale;
	m_degree = _degree;
	m_col = _col;

	m_texName = _texname;

	mp_TexRenderer->SetTexture(m_texName);
	m_texNameBuffer = m_texName;
}

void UISprite::update()
{
	if (m_texNameBuffer != m_texName) {
		mp_TexRenderer->SetTexture(m_texName);
		m_texNameBuffer = m_texName;
	}
}

void UISprite::input()
{
}

void UISprite::draw()
{
	mp_TexRenderer->TextureDraw(m_offset, m_col, m_scale, m_degree);
}

void UISprite::AlignPivotCenter()
{
	m_offset = { -mp_TexRenderer->GetTexture()->getWidth() / 2 * m_scale.x, -mp_TexRenderer->GetTexture()->getHeight() / 2 * m_scale.y };
}
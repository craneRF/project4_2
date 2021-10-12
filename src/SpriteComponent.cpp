#include "SpriteComponent.h"
#include "GameActor.h"

SpriteComponent::SpriteComponent(GameActor* _gactor) :
	Component(_gactor, "SpriteComponent")
	, m_offset({ 0.0f, 0.0f, 0.0f })
	, m_col(ofColor::white)
	, m_scale({ 1.0f, 1.0f, 1.0f })
	, m_texName("NoSearch.png")
	, m_texNameBuffer(m_texName)
	,m_degree(0.0f)
{
	mp_TexRenderer = make_unique<TextureRenderer>();
	mp_TexRenderer->SetTexture(m_texName);

	mp_gActor->drawfunc = std::bind(&SpriteComponent::draw, this);
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::initialize(const string& _texname, ofVec3f _offset, ofVec3f _scale, float _degree, ofColor _col)
{
	m_offset = _offset;
	m_scale = _scale;
	m_degree = _degree;
	m_col = _col;

	m_texName = _texname;

	mp_TexRenderer->SetTexture(m_texName);
	m_texNameBuffer = m_texName;
}

void SpriteComponent::update(float _deltatime)
{
	if (m_texNameBuffer != m_texName) {
		mp_TexRenderer->SetTexture(m_texName);
		m_texNameBuffer = m_texName;
	}
}

void SpriteComponent::input(float _deltatime)
{
}

void SpriteComponent::draw()
{
	if (m_CpntDrawState == Component::ComponentDrawState::EVisible) {
		mp_TexRenderer->TextureDraw(m_offset, m_col, m_scale, m_degree);
	}
}

void SpriteComponent::AlignPivotCenter()
{
	m_offset = { -mp_TexRenderer->GetTexture()->getWidth() / 2 * m_scale.x, -mp_TexRenderer->GetTexture()->getHeight() / 2 * m_scale.y};
}


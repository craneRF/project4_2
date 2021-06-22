#include "SpriteComponent.h"
#include "GameActor.h"

SpriteComponent::SpriteComponent(GameActor* _gactor) :
	Component(_gactor, "SpriteComponent")
	, m_texName("NoSearch.png")
	, m_texNameBuffer(m_texName)
	, m_spriteState(SpriteState::EVisibled)
{
	mp_TexRenderer = make_unique<TextureRenderer>();

	mp_gActor->drawfunc = std::bind(&SpriteComponent::draw, this);
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::initialize(const string& _texname, ofVec3f _offset, ofColor _col, ofVec3f _scale)
{
	Offset() = _offset;
	Color() = _col;
	Scale() = _scale;

	m_texName = _texname;

	mp_TexRenderer->SetTexture(m_texName);
	m_texNameBuffer = m_texName;

	mp_gActor->drawfunc = std::bind(&SpriteComponent::draw, this);
}

void SpriteComponent::update(float _deltatime)
{
	if (m_texNameBuffer != m_texName) {
		mp_TexRenderer->SetTexture(m_texName);
		m_texNameBuffer = m_texName;
	}
}

void SpriteComponent::draw()
{
	if (m_spriteState == SpriteState::EInVisibled) {
		return;
	}
	mp_TexRenderer->TextureDraw();
}

void SpriteComponent::AlignPivotCenter()
{
	Offset() = { -mp_TexRenderer->GetTexture()->getWidth() / 2 * Scale().x, -mp_TexRenderer->GetTexture()->getHeight() / 2 * Scale().y};
}


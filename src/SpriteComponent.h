#pragma once
#include "ofMain.h"
#include "Component.h"
#include "Renderer.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(GameActor* _gactor);
	virtual ~SpriteComponent();

	enum class SpriteState {
		EVisibled
		, EInVisibled
	};

	void initialize(const string& _texname = "NoSearch.png", ofVec3f _offset = { 0,0,0 }, ofColor _col = ofColor::white, ofVec3f _scale = { 1, 1, 1 });
	virtual void update(float _deltatime);
	void draw();	

	void AlignPivotCenter();

private:
	string m_texName;
	SpriteState m_spriteState;

	//update���ɃT�C�Y�ƃt�H���g�l�[�����ω����ꂽ���p�̕ϐ�
	string m_texNameBuffer;         //���݂̉摜���i�[�ϐ�

	unique_ptr<TextureRenderer> mp_TexRenderer;

public:
	inline ofVec3f& Offset() 
	{ 
		return mp_TexRenderer->Offset();
	}
	inline ofColor& Color()
	{ 
		return mp_TexRenderer->Color();
	}
	inline ofVec3f& Scale() 
	{ 
		return mp_TexRenderer->Scale();
	}

	inline string& TexName()
	{
		return m_texName;
	}
	inline SpriteState& SpriteState() 
	{
		return m_spriteState; 
	}
};
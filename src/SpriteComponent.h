#pragma once
#include "ofMain.h"
#include "Component.h"
#include "Renderer.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(GameActor* _gactor);
	virtual ~SpriteComponent();

	void initialize(const string& _texname = "NoSearch.png", ofVec3f _offset = { 0,0,0 }, ofColor _col = ofColor::white, ofVec3f _scale = { 1, 1, 1 });
	virtual void update(float _deltatime);
	void draw();	

	void AlignPivotCenter();

private:
	ofVec3f m_offset;
	ofColor m_col;
	ofVec3f m_scale;
	string m_texName;

	//update���ɃT�C�Y�ƃt�H���g�l�[�����ω����ꂽ���p�̕ϐ�
	string m_texNameBuffer;         //���݂̉摜���i�[�ϐ�

	unique_ptr<TextureRenderer> mp_TexRenderer;

public:
	inline ofVec3f& Offset() 
	{ 
		return m_offset;
	}
	inline ofColor& Color()
	{ 
		return m_col;
	}
	inline ofVec3f& Scale() 
	{ 
		return m_scale;
	}

	inline string& TexName()
	{
		return m_texName;
	}
};
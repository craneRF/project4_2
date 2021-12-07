#pragma once
#include "ofMain.h"
#include "Component.h"
#include "Renderer.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(GameActor* _gactor);
	virtual ~SpriteComponent();

	void initialize(const string& _texname = "NoSearch.png", ofVec3f _offset = { 0,0,0 }, ofVec3f _scale = { 1, 1, 1 }, float _degree = 0.0f, ofColor _col = ofColor::white);
	virtual void update();
	void input() override;
	void draw();

	void AlignPivotCenter();
private:

	ofVec3f m_offset;
	ofVec3f m_scale;
	float m_degree;
	ofColor m_col;
	string m_texName;

	//update中にサイズとフォントネームが変化された時用の変数
	string m_texNameBuffer;         //現在の画像名格納変数

	unique_ptr<TextureRenderer> mp_TexRenderer;

public:

	inline ofVec3f& Offset()
	{
		return m_offset;
	}
	inline ofVec3f& Scale()
	{
		return m_scale;
	}
	inline float& Degree()
	{
		return m_degree;
	}
	inline ofColor& Color()
	{
		return m_col;
	}

	//初期化の時に使わない。初期化の時はinitialize()を使う。
	inline string& TexName()
	{
		return m_texName;
	}

	inline ofVec3f ImageSize() { return ofVec3f(mp_TexRenderer->GetTexture()->getWidth(), mp_TexRenderer->GetTexture()->getHeight()); }
};
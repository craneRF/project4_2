#pragma once
#include "ofMain.h"
#include "UIActor.h"

class UISprite : public UIActor
{
public:
	UISprite(string _name = "");
	~UISprite();

	void initialize(const string& _texname = "NoSearch.png", float _angle = 0.0f, ofColor _col = ofColor::white);

	void update(float _deltaTime) override;
	void input(float _deltaTime) override;
	void draw() override;

	void AlignPivotCenter();

private:
	ofVec3f m_offset;
	ofColor m_col;
	string m_texName;

	//update中にサイズとフォントネームが変化された時用の変数
	string m_texNameBuffer;         //現在の画像名格納変数

public:
	inline ofVec3f& Offset()
	{
		return m_offset;
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
};


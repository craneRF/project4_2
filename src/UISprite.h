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

	//update���ɃT�C�Y�ƃt�H���g�l�[�����ω����ꂽ���p�̕ϐ�
	string m_texNameBuffer;         //���݂̉摜���i�[�ϐ�

public:
	inline ofVec3f& Offset()
	{
		return m_offset;
	}
	inline ofColor& Color()
	{
		return m_col;
	}

	//�������̎��Ɏg��Ȃ��B�������̎���initialize()���g���B
	inline string& TexName()
	{
		return m_texName;
	}
};


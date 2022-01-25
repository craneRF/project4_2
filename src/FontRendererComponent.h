#pragma once
#include "ofMain.h"
#include "Component.h"
#include "Renderer.h"

class GameActor;

class FontRendererComponent :
	public Component
{
private:
	string m_str;
	int m_size;
	ofVec3f m_offset;
	ofColor m_col;
	ofVec3f m_scale;
	string m_fontName;

	//update���ɃT�C�Y�ƃt�H���g�l�[�����ω����ꂽ���p�̕ϐ�
	int m_sizeBuffer;         //���݂̃T�C�Y�i�[�ϐ�
	string m_fontNameBuffer;  //���݂̃t�H���g�l�[���i�[�ϐ�

	unique_ptr<FontRenderer> mp_fontRenderer;

public:
	FontRendererComponent(GameActor* _gactor);
	virtual ~FontRendererComponent();
	void initialize(const string& _str = "Not String", int _size = 18, ofVec3f _offset = { 0,0,0 }, ofColor _col = ofColor::white, ofVec3f _scale = {1, 1, 1}, const string& _fontname = "keifont.ttf");
	virtual void update();
	void input() override;
	void draw();
	void AlignPivotCenter();

	inline string& String()
	{ 
		return m_str;
	}
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

	inline int& Size() 
	{ 
		return m_size; 
	}
	inline string& FontName()
	{ 
		return m_fontName; 
	}
};
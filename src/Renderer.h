#pragma once
#include "ofMain.h"
#include "ofApp.h"

class FontRenderer
{
public:
	FontRenderer();
	~FontRenderer();

	void FontDraw();

private:
	string m_str;
	int m_size;
	ofVec3f m_offset;
	ofColor m_col;
	ofVec3f m_scale;
	string m_fontName;

	/*int m_currentFontSize;
	string m_currentFontName;*/

	shared_ptr<ofTrueTypeFont> mp_currentFont;

public:
	inline string& String()
	{
		return m_str;
	}
	inline ofVec3f& OffSet()
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

	inline void SetSize(int _size)
	{
		m_size = _size;
		mp_currentFont = ofApp::getInstance()->mp_font->GetFontMap().find(m_fontName)->second.find(m_size)->second;
	}
	inline void SetFontName(const string& _fontname)
	{
		m_fontName = _fontname;
		mp_currentFont = ofApp::getInstance()->mp_font->GetFontMap().find(m_fontName)->second.find(m_size)->second;
	}
};

class TextureRenderer
{
public:
	TextureRenderer();
	~TextureRenderer();

	void TextureDraw();

private:
	ofVec3f m_offset;
	ofColor m_col;
	ofVec3f m_scale;
	string m_texName;

	//shared_ptr<ofImage> mp_image;
	ofImage* mp_image;

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

	/*inline const shared_ptr<ofImage> GetTexture()
	{
		return mp_image;
	}*/
	inline const ofImage* GetTexture()
	{
		return mp_image;
	}

	inline void SetTexture(const string & _texname)
	{
		m_texName = _texname;
		mp_image = ofApp::getInstance()->mp_texture->GetImage("images/" + m_texName);
	}
};


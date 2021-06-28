#pragma once
#include "ofMain.h"

class FontRenderer
{
public:
	FontRenderer();
	~FontRenderer();

	void SetSize(int _size);
	void SetFontName(const string& _fontname);

	void FontDraw(string _str, ofVec3f _offset, ofColor _col, ofVec3f _scale);

private:
	int m_size;
	string m_fontName;

	shared_ptr<ofTrueTypeFont> mp_currentFont;
};

class TextureRenderer
{
public:
	TextureRenderer();
	~TextureRenderer();

	void SetTexture(const string & _texname = "NoSearch.png");

	void TextureDraw(ofVec3f _offset, ofColor _col, ofVec3f _scale);

private:
	string m_texName;

	ofImage* mp_image;

public:
	inline const ofImage* GetTexture()
	{
		return mp_image;
	}
};


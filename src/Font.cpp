#include "Font.h"
#include "ResourceManager.h"

Font::Font()
	:m_fontname("")
	,mp_fontManager(nullptr)
{
	m_FontData.clear();

	Load();
}

Font::~Font()
{
	m_FontData.clear();
}

bool Font::Load()
{
	mp_fontManager = make_unique<ResourceManager<string>>();
	mp_fontManager->loadContentFromFile("FontRes.txt");

	for (const auto& fontname : mp_fontManager->getMap()) {
		unordered_map<int, shared_ptr<ofTrueTypeFont>> SizeMap;  //サイズの管理マップ
		for (const auto& size : m_fontSize) {
			shared_ptr<ofTrueTypeFont> pTTFont = make_shared<ofTrueTypeFont>();
			auto fontsettings = ofTrueTypeFontSettings(fontname.second.c_str(), size);
			fontsettings.addRanges(ofAlphabet::Latin);
			fontsettings.addRanges(ofAlphabet::Japanese);
			if (!pTTFont->load(fontsettings)) {  //mp_TTFontへfontsettingを読み込み
				return false;
			}

			SizeMap.emplace(size, pTTFont);
		}
		m_fontname = fontname.second;
		m_fontname.erase(m_fontname.begin(), m_fontname.begin() + 6);
		m_FontData.emplace(m_fontname, SizeMap);
	}
	return true;
}
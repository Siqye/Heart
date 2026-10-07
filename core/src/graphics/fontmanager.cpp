#include "fontmanager.hpp"

namespace heartCore { namespace graphics {
	FontManager::FontManager() {}
	
	FontManager::FontManager(const char* fontFolder) {
		for (const auto& entry : std::filesystem::directory_iterator(fontFolder)) {

			if (entry.path().extension() == ".ttf") {
				m_fontsLib.push_back(new Font(entry.path().string().c_str()));
			}
		}
	}

	FontManager::~FontManager() {
		for (Font* font : m_fontsLib) delete font;
	}

	void FontManager::loadFontFromFile(const char* fontPath) {
		m_fontsLib.push_back(new Font(fontPath));
	}

	void FontManager::loadFontsFolder(const char* folderPath) {
		for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
			
			if (entry.path().extension() == ".ttf") {
				m_fontsLib.push_back(new Font(entry.path().string().c_str()));
			}
		}
	}

	Font* FontManager::getFontbyID(int fontID) {
		if (fontID < 0 || fontID >= m_fontsLib.size()) return new Font("test/fonts/RobotoMobo.ttf");
		return m_fontsLib[fontID];
	}
} }
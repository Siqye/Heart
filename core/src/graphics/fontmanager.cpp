#include "fontmanager.hpp"

namespace heartCore { namespace graphics {
	FontManager::FontManager() {}
	
	FontManager::FontManager(const char* fontFolder) {
		for (const auto& entry : std::filesystem::directory_iterator(fontFolder)) {

			if (entry.path().extension() == ".ttf") {
				m_fontsLib.push_back(std::make_shared<Font>(entry.path().string().c_str()));
			}
		}
	}

	FontManager::~FontManager() {
	}

	void FontManager::loadFontFromFile(const char* fontPath) {
		m_fontsLib.push_back(std::make_shared<Font>(fontPath));
	}

	void FontManager::loadFontsFolder(const char* folderPath) {
		for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
			
			if (entry.path().extension() == ".ttf") {
				m_fontsLib.push_back(std::make_shared<Font>(entry.path().string().c_str()));
			}
		}
	}

	std::shared_ptr<Font> FontManager::getFontbyID(int fontID) {
		if (fontID < 0 || fontID >= m_fontsLib.size()) return std::make_shared<Font>("test/fonts/RobotoMobo.ttf");
		return m_fontsLib[fontID];
	}
} }
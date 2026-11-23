#include "fontmanager.hpp"

namespace heartCore { namespace graphics {
	namespace API {
	FontManager::FontManager() {}
	
	FontManager::FontManager(const char* fontFolder) {
		for (const auto& entry : std::filesystem::directory_iterator(fontFolder)) {

			if (entry.path().extension() == ".ttf") {
				m_fontsLib.push_back(std::make_shared<Font>(entry.path().string().c_str(), entry.path().filename().string()));
			}
		}
	}

	FontManager::~FontManager() {}

	void FontManager::loadFontsFolder(const char* folderPath) {
		for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
			
			if (entry.path().extension() == ".ttf") {
				m_fontsLib.push_back(std::make_shared<Font>(entry.path().string().c_str(), entry.path().filename().string()));
			}
		}
	}

	std::shared_ptr<Font> FontManager::getFontbyID(int fontID) {
		if (fontID < 0 || fontID >= m_fontsLib.size()) return NULL;
			return m_fontsLib[fontID];
	}

	std::shared_ptr<Font> FontManager::getFont(const std::string& fontName) {
		int vecSize = m_fontsLib.size();
		for (int i = 0; i < vecSize;i++) {
			if (m_fontsLib[i]->getName() == fontName)
				return m_fontsLib[i];
		}
		return NULL;
	}
	} 
} }

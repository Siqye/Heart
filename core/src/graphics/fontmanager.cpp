#include "fontmanager.hpp"

namespace heartCore { namespace graphics {
	FontManager::FontManager() {
		
	}
	
	FontManager::FontManager(const char* fontFolder) {
		for (const auto& entry : std::filesystem::directory_iterator(fontFolder)) {
			std::cout << entry.path() << std::endl;
			
			Font font = Font("RobotoMono.ttf", "robotomono");

			std::filesystem::path fileName = entry.path().filename();
			std::filesystem::path fileExtention = entry.path().extension();
			std::cout << fileName << std::endl;
			std::cout << fileExtention << std::endl;

			if (fileExtention == ".ttf") {
				font = Font(entry.path().string().c_str(), entry.path().filename().string().c_str());
				m_fontsLib.push_back(font);
			}
		}
	}

	FontManager::~FontManager() {}

	void FontManager::loadFontFromFile(const char* fontPath) {
		m_fontsLib.push_back(Font(fontPath, fontPath));
	}

	void FontManager::loadFontsFolder(const char* folderPath) {
		for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
			std::cout << entry.path() << std::endl;

			Font font = Font("RobotoMono.ttf", "robotomono");

			std::filesystem::path fileName = entry.path().filename();
			std::filesystem::path fileExtention = entry.path().extension();
			std::cout << fileName << std::endl;
			std::cout << fileExtention << std::endl;

			if (fileExtention == ".ttf") {
				font = Font(entry.path().string().c_str(), entry.path().filename().string().c_str());
				m_fontsLib.push_back(font);
			}
		}
	}

	Font FontManager::getFontbyName(const char* fontName) {
		return Font("RobotoMono.ttf", "");
	}

	Font FontManager::getFontbyID(int fontID) {
		if (fontID <= 0 || fontID > m_fontsLib.size()) return Font("RobotoMobo.ttf", "");
		return m_fontsLib[fontID];
	}
} }
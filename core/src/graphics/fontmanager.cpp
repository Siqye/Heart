#include "fontmanager.hpp"

namespace heartCore { namespace graphics {
	FontManager::FontManager() {
		
	}
	
	FontManager::FontManager(const char* fontFolder) {
		for (const auto& entry : std::filesystem::directory_iterator(fontFolder)) {
			std::cout << entry.path() << std::endl;
			
			Font font = Font("RobotoMono.ttf");

			std::filesystem::path fileName = entry.path().filename();
			std::filesystem::path fileExtention = entry.path().extension();
			std::cout << fileName << std::endl;
			std::cout << fileExtention << std::endl;

			if (fileExtention == ".ttf") {
				font = Font(entry.path().string().c_str());
				m_fontsLib.push_back(font);
			}
		}
	}

	FontManager::~FontManager() {}

	void FontManager::loadFontFromFile(const char* fontPath) {
		m_fontsLib.push_back(Font(fontPath));
	}

	void FontManager::loadFontsFolder(const char* folderPath) {
		for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
			std::cout << entry.path() << std::endl;

			Font font = Font("RobotoMono.ttf");

			std::filesystem::path fileName = entry.path().filename();
			std::filesystem::path fileExtention = entry.path().extension();
			std::cout << fileName << std::endl;
			std::cout << fileExtention << std::endl;

			if (fileExtention == ".ttf") {
				font = Font(entry.path().string().c_str());
				m_fontsLib.push_back(font);
			}
		}
	}

	Font FontManager::getFontbyName(const char* fontName) {
		return Font("RobotoMono.ttf");
	}

	Font FontManager::getFontbyID(int fontID) {
		return Font("RobotoMono.ttf");
	}
} }
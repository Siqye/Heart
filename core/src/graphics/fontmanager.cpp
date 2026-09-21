#include "fontmanager.hpp"

namespace heartCore { namespace graphics {
	FontManager::FontManager() {
		
	}

	std::string FontManager::get_file_extention(std::string file) {
		std::string result1 = "";
		std::string result2 = "";
		for (int i = file.size(); i > 0; i--) {
			if (file[i] == '.') break;
			result1 += file[i];
		}
		for (int i = result1.size(); i > 0;i--) {
			result2 += result1[i];
		}
		if (file == result2) {
			return NULL;
		}
		else {
			return result2;
		}
	}
	
	std::string FontManager::get_file_name(std::string path) {
		std::string result1 = "";
		std::string result2 = "";//
		for (int i = path.size(); i > 0; i--) {
			if (path[i] == '/' || path[i] == '\\') break;
			result1 += path[i];
		}
		for (int i = result1.size(); i > 0;i--) {
			result2 += result1[i];
		}
		return result2;
	}
	
	FontManager::FontManager(const char* fontFolder) {
		std::string path = "test/";
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			std::cout << entry.path() << std::endl;
			
			Font font = Font("RobotoMono.ttf");

			std::string stringPath{ entry.path().string() };
			std::string fileName = get_file_name(stringPath);
			std::string fileExtention = get_file_extention(fileName);
			std::cout << fileName << std::endl;
			std::cout << fileExtention << std::endl;

			if (fileExtention == "ttf") {
				font = Font(path + fileName);
				m_fontsLib.push_back(font);
			}
		}
			
	}

	FontManager::~FontManager() {}

	Font FontManager::loadFontFromFile(const char* fontPath) {
		return Font("RobotoMono.ttf");
	}

	Font FontManager::loadFontsFolder(const char* folderPath) {
		return Font("RobotoMono.ttf");
	}

	Font FontManager::getFontbyName(const char* fontName) {
		return Font("RobotoMono.ttf");
	}

	Font FontManager::getFontbyID(int fontID) {
		return Font("RobotoMono.ttf");
	}
} }
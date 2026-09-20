#include "fontmanager.hpp"

namespace heartCore { namespace graphics {
	FontManager::FontManager() {

	}

	const char* FontManager::get_file_extention(std::string file) {
		std::string result1 = "";
		std::string result2 = "";
		for (int i = file.size(); i > 0; i) {
			if (file[i] != '.' ) result1 += file[i];
		}
		for (int i = 0; i < result1.size();i++) {
			result2 += result1[i];
		}
		if (file == result2) {
			return NULL;
		}
		else {
			return result2.c_str();
		}
	}

	const char* FontManager::get_file_name(std::string path) {
		std::string result1 = "";
		std::string result2 = "";
		for (int i = path.size(); i > 0; i) {
			if (path[i] != '/' || path[i] == '\\') result1 += path[i];
		}
		for (int i = 0; i < result1.size();i++) {
			result2 += result1[i];
		}
		return result2.c_str();
	}

	FontManager::FontManager(const char* fontFolder) {
		std::string path = "test/";
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			std::cout << entry.path() << std::endl;
			std::string filePath = entry.path.generic_string();
			std::cout << get_file_name(filePath) << std::endl;
		}
			
	}

	FontManager::~FontManager() {}

	Font FontManager::loadFontFromFile(const char* fontPath) {
		return NULL;
	}

	Font FontManager::loadFontsFolder(const char* folderPath) {
		return NULL;
	}

	Font FontManager::getFontbyName(const char* fontName) {
		return NULL;
	}

	Font FontManager::getFontbyID(int fontID) {
		return NULL;
	}
} }
#pragma once

#include "font.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>

namespace heartCore { namespace graphics {
	class FontManager {
	private:
		std::vector<Font> m_fontsLib;
		std::string get_file_extention(std::string file);
		std::string get_file_name(std::string path);
	public:
		FontManager();
		FontManager(const char* fontFolder);
		~FontManager();

		Font loadFontFromFile(const char* fontPath);
		Font loadFontsFolder(const char* folderPath);

		Font getFontbyName(const char* fontName);
		Font getFontbyID(int fontID);
	};
} }
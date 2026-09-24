#pragma once

#include "font.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <memory>

namespace heartCore { namespace graphics {
	class FontManager {
	private:
		std::vector<Font> m_fontsLib;
	public:
		FontManager();
		FontManager(const char* fontFolder);
		~FontManager();

		void loadFontFromFile(const char* fontPath);
		void loadFontsFolder(const char* folderPath);

		Font getFontbyID(int fontID);
	};
} }
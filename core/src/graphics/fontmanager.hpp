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
		std::vector<std::shared_ptr<Font>> m_fontsLib;
	public:
		FontManager();
		FontManager(const char* fontFolder);
		~FontManager();
		
		void loadFontsFolder(const char* folderPath);

		std::shared_ptr<Font> getFontbyID(int fontID);
		std::shared_ptr<Font> getFont(const std::string& fontName);
	};
} }
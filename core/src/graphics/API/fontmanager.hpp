#pragma once

#include "../font.hpp"

namespace heartCore { namespace graphics {
	class FontManager {
	private:
	public:
		FontManager();
		~FontManager();

		Font loadFontFromFile(const char* fontPath);

		Font loadFontFolder(const char* folderPath);

	};
} }
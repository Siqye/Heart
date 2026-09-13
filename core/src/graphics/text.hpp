#pragma once
#include <freetype-gl.h>
#include <text-buffer.h>
#include <font-manager.h>
#include "texture.hpp"

namespace heartCore { namespace graphics {

	class Label {
		text_buffer_t* textBuffer;
		font_manager_t* font_manager;
		const char* text, fontPath;
		Texture textTexture;


		Label(const char* fontPath, const char* text);
		~Label();
	};

} }
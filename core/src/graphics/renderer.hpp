#pragma once
#include <glew.h>
#include <vector>
#include "../maths/maths.hpp"
#include <cstddef>
#include "../../ext/freetype-gl/freetype-gl.h"
#include "../utils/char_loader.h"

namespace heartCore { namespace graphics { 
	class StaticSprite;
	struct VertexData;
	class Texture;

	class Renderer {
	protected:
		GLuint VAO, VBO, IBO;
	public:
		Renderer() {}
		~Renderer() {}

		virtual void push(const maths::mat4& matrix, bool override = false) {}
		virtual void pop() {}

		virtual void begin() {}
		virtual void submit(const StaticSprite* sprite) = 0;
		virtual void submitText(std::string text, maths::vec3 position, maths::vec4 col) = 0;
		virtual void end() {}
		virtual void draw() = 0;
	};
} }
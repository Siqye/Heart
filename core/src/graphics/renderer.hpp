#pragma once
#include <glew.h>
#include <vector>
#include "../maths/maths.hpp"
#include <cstddef>
#include "font.hpp"
#include "../utils/char_loader.h"
#include "../config.h"

namespace heartCore { namespace graphics { 
	class StaticSprite;
	struct VertexData;
	class Texture;

	class Renderer {
	protected:
		GLuint VAO, VBO, IBO;

		std::vector<maths::mat4> m_transformStack;
		const maths::mat4* m_transformBack;
	public:
		Renderer() {}
		~Renderer() {}

		virtual inline void push(const maths::mat4& matrix, bool override = false) {
			if (override) m_transformStack.push_back(matrix);

			else m_transformStack.push_back(m_transformStack.back() * matrix);

			m_transformBack = &m_transformStack.back();
		}

		virtual inline void pop() {
			if (m_transformStack.size() > 1) m_transformStack.pop_back();
			m_transformBack = &m_transformStack.back();
		}

		virtual void begin() {}
		virtual void submit(const StaticSprite* sprite) = 0;
		virtual void submitText(std::string text, float scale, maths::vec3 position, maths::vec4 col, Font font) = 0;
		virtual void end() {}
		virtual void draw() = 0;
	};
} }
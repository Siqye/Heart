#pragma once
#include <glew.h>
#include "../utils/image_loader.hpp"
#include <string>

namespace heartCore { namespace graphics {
	class Texture {
	private:
		std::string m_texturePath;
		GLsizei m_width, m_height;
		GLuint m_texID;

		GLuint load();
	public://
		Texture(const char* texturePath);
		~Texture();

		void bind() const;
		void unbind() const;
	

		inline const unsigned int getWidth() const { return m_width; }
		inline const unsigned int getHeight() const { return m_height; }
		inline const GLuint getTID() const { return m_texID; }
	};
} }
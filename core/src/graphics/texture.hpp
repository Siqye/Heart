#pragma once
#include <glew.h>
#include "../utils/image_loader.hpp"

namespace heartCore { namespace graphics {
	class Texture {
	private:
		const char* m_texturePath;
		GLsizei m_width, m_height;
		GLuint m_texID;

		GLuint load();
	public:
		Texture(GLuint data);
		Texture(const char* texturePath);
		~Texture();

		void bind() const;
		void unbind() const;
	

		inline const unsigned int getWidth() const { return m_width; }
		inline const unsigned int getHeight() const { return m_height; }
		inline const GLuint getTID() const { return m_texID; }
	};
} }
#include "texture.hpp"

namespace heartCore { namespace graphics {

	Texture::Texture(const char* texturePath) 
		: m_texturePath(texturePath) 
	{
		m_texID = load();
	}

	GLuint Texture::load() {
		BYTE* pixels = load_image(m_texturePath, &m_width, &m_height);
		GLuint result;
		if (pixels == nullptr) return 0;
		glGenTextures(1, &result);
		glBindTexture(GL_TEXTURE_2D, result);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);

		glBindTexture(GL_TEXTURE_2D, 0);

		return result;
	}

	Texture::~Texture() { }

	void Texture::bind() const {
		glBindTexture(GL_TEXTURE_2D, m_texID);
	}

	void Texture::unbind() const {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
} }
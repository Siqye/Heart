#pragma once
#include <glew.h>
#include <iostream>
#include "../utils/file_reader.hpp"

namespace heartCore { namespace graphics {
	class Shader
	{
	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();
		void bind() const;
		void unbind() const;
	private:
		GLuint compileShader(const char* source, GLenum type);

		const char* m_vertexPath;
		const char* m_fragmentPath;
		GLuint m_programID;
	};
} }
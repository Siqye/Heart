#pragma once
#include <glew.h>
#include <iostream>
#include "../maths/maths.hpp"
#include "../utils/file_reader.hpp"

namespace heartCore { namespace graphics {
	class Shader
	{
	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();
		void bind() const;
		void unbind() const;

		void setUniform1i(const GLchar* name, int value);
		void setUniform1f(const GLchar* name, float value);

		void setUniform2f(const GLchar* name, const maths::vec2& vector);
		void setUniform3f(const GLchar* name, const maths::vec3& vector);
		void setUniform4f(const GLchar* name, const maths::vec4& vector);
		void setUniformMat4f(const GLchar* name, const maths::mat4& matrix);
	private:
		GLuint compileShader(const char* source, GLenum type);
		GLuint getUniformLocation(const GLchar* name);

		const char* m_vertexPath;
		const char* m_fragmentPath;
		GLuint m_programID;
	};
} }
#pragma once
#include <glew.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include "../../maths/maths.hpp"
#include "../../utils/file_reader.hpp"

namespace heartCore { namespace graphics {
	namespace API {
	class Shader
	{
	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();
		void bind() const;
		void unbind() const;

		void setUniform1i(const GLchar* name, int value);
		void setUniform1f(const GLchar* name, float value);
		void setUniform1fv(const GLchar* name, int count, float* value);
		void setUniform1iv(const GLchar* name, int count, int* value);

		void setUniform2f(const GLchar* name, const maths::vec2& vector);
		void setUniform3f(const GLchar* name, const maths::vec3& vector);
		void setUniform4f(const GLchar* name, const maths::vec4& vector);
		void setUniformMat4f(const GLchar* name, const maths::mat4& matrix);
	private:
		GLuint compileShader(const char* source, GLenum type);
		GLint getUniformLocation(const GLchar* name);

		std::unordered_map<std::string, GLint> m_uniformCache;

		const char* m_vertexPath;
		const char* m_fragmentPath;
		GLuint m_programID;
	};
	}
} }

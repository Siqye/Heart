#include "shader.hpp"


namespace heartCore { namespace graphics {
	Shader::Shader(const char* vertexPath, const char* fragmentPath)
	{
		m_programID = glCreateProgram();

		GLuint vertexShader = compileShader(vertexPath, GL_VERTEX_SHADER);
		GLuint fragmentShader = compileShader(fragmentPath, GL_FRAGMENT_SHADER);
		glAttachShader(m_programID, vertexShader);
		glAttachShader(m_programID, fragmentShader);
		GLint ok;
		glLinkProgram(m_programID);glGetProgramiv(m_programID, GL_LINK_STATUS, &ok);
		if (!ok) {
			GLint len; glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &len);
			std::string log(len, '\0'); glGetProgramInfoLog(m_programID, len, nullptr, &log[0]);
			std::cerr << "Program link error: " << log << std::endl;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glUseProgram(m_programID);
	}

	GLuint Shader::compileShader(const char* shaderPath, GLenum type)
	{
		std::string shaderSource = readFile(shaderPath);
		const char* shaderSourceCStr = shaderSource.c_str();
		GLuint shaderID = glCreateShader(type);
		glShaderSource(shaderID, 1, &shaderSourceCStr, nullptr);
		glCompileShader(shaderID);
		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLint len; glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &len);
			std::string log(len, '\0'); glGetProgramInfoLog(m_programID, len, nullptr, &log[0]);
			std::cerr << "Program link error: " << log << std::endl;
		}
		return shaderID;
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_programID);
	}
	void Shader::bind() const
	{
		glUseProgram(m_programID);
	}
	void Shader::unbind() const
	{
		glUseProgram(0);
	}

	void Shader::setUniform1i(const GLchar* name, int value) {
		glUniform1i(getUniformLocation(name), value);
	}
	void Shader::setUniform1f(const GLchar* name, float value) {
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform2f(const GLchar* name, const maths::vec2& vector) {
		glUniform2f(getUniformLocation(name), vector.x, vector.y);
	}
	void Shader::setUniform3f(const GLchar* name, const maths::vec3& vector) {
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
	}
	void Shader::setUniform4f(const GLchar* name, const maths::vec4& vector) {
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}
	void Shader::setUniformMat4f(const GLchar* name, const maths::mat4& matrix) {
		glUniformMatrix4fv(getUniformLocation(name),1, GL_FALSE, matrix.elements);
	}

	GLuint Shader::getUniformLocation(const GLchar* name) {
		return glGetUniformLocation(m_programID, name);
	}
} }
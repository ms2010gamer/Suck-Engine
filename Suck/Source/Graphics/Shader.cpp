#include "Graphics/Shader.h"

Shader::Shader(const char* VertPath, const char* FragPath)
: m_VertSource(VertPath), m_FragSource(FragPath)
{
	m_ShaderID = load();
}

GLuint Shader::load()
{
	GLuint program = glCreateProgram();

	std::string vsStr = FileUtil::read_file(m_VertSource);
	std::string fsStr = FileUtil::read_file(m_FragSource);

	const char* vs = vsStr.c_str();
	const char* fs = fsStr.c_str();

	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex, 1, &vs, NULL);
	glCompileShader(vertex);

	GLint result;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(vertex, length, &length, &error[0]);
		std::cout << "Failed To Compile Vertex Shader!" << std::endl << &error[0] << std::endl;
		glDeleteShader(vertex);
		return 0;
	}

	glShaderSource(fragment, 1, &fs, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(fragment, length, &length, &error[0]);
		std::cout << "Failed To Compile Fragment Shader!" << std::endl << &error[0] << std::endl;
		glDeleteShader(fragment);
		return 0;
	}

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return program;
}

void Shader::enable() const
{
	glUseProgram(m_ShaderID);
}

void Shader::disable() const
{
	glDeleteProgram(m_ShaderID);
}
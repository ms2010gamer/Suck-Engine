#pragma once

#include <ThirdParty/GLAD/glad.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class FileUtil
{
public:
	static std::string read_file(const std::string& filepath) {
		std::ifstream ifs((filepath).c_str());
		std::string content(
			std::istreambuf_iterator<char>(ifs.rdbuf()),
			std::istreambuf_iterator<char>()
		);
		return content;
	}
};

class Shader
{
private:
	GLuint m_ShaderID;
	const char* m_VertSource;
	const char* m_FragSource;
	GLuint load();
public:
	Shader(const char* VertPath, const char* FragPath);

	int getUniform(const char* name);

	void enable() const;
	void disable() const;
};
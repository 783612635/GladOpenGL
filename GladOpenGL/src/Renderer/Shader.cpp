#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* VertexSPath, const char* FragmentSPath)
{
	std::string VertexCode;
	std::string FragmentCode;
	std::ifstream VSFile;
	std::ifstream FSFile;
	// 保证ifstream对象可以抛出异常：
	VSFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	FSFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		VSFile.open(VertexSPath);
		FSFile.open(FragmentSPath);

		std::stringstream vsStream, fsStream;
		vsStream << VSFile.rdbuf();
		fsStream << FSFile.rdbuf();

		VSFile.close();
		FSFile.close();

		VertexCode = vsStream.str();
		FragmentCode = fsStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ!" << std::endl;
	}

	const char* vShaderCode = VertexCode.c_str();
	const char* fShaderCode = FragmentCode.c_str();

	unsigned int vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	GetSourceAndCompile(vertex, vShaderCode);
	GetSourceAndCompile(fragment, fShaderCode);

	CreateProgram(vertex, fragment);

	// 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use() const
{
	glUseProgram(shaderProgramId);
}

void Shader::GetSourceAndCompile(unsigned int ShaderID, const char* source)
{
	int success;
	char infoLog[512];

	glShaderSource(ShaderID, 1, &source, NULL);
	glCompileShader(ShaderID);
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(ShaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << ShaderID << "::COMPILATION_FAILED :: {\n" << infoLog << "}" << std::endl;
	};
}

void Shader::CreateProgram(unsigned int vsID, unsigned int fsID)
{
	int success;
	char infoLog[512];

	shaderProgramId = glCreateProgram();
	glAttachShader(shaderProgramId, vsID);
	glAttachShader(shaderProgramId, fsID);
	glLinkProgram(shaderProgramId);
	glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgramId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED:: --- " << infoLog << std::endl;
	}
}

void Shader::DeleteShader()
{
	glDeleteShader(shaderProgramId);
}

void Shader::SetUniform1i(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(shaderProgramId, name.c_str()), value);
}

void Shader::SetUniform1f(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(shaderProgramId, name.c_str()), value);
}

void Shader::SetUniform3f(const std::string& name, glm::vec3 v) const
{
	glUniform3f(glGetUniformLocation(shaderProgramId, name.c_str()), v.x, v.y, v.z);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(glGetUniformLocation(shaderProgramId, name.c_str()), v0, v1, v2, v3);
}

void Shader::SetUniformMat4(const std::string& name, glm::mat4 m)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramId, name.c_str()), 1,GL_FALSE,glm::value_ptr(m));
}


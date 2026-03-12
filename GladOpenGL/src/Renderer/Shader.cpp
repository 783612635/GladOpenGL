#include "Shader.h"

void Shader::GetSourceAndCompile(std::string source)
{
	const char* src = source.c_str();
	glShaderSource(shaderId, 1, &src, NULL);
	glCompileShader(shaderId);
}

void Shader::DeleteShader()
{
	glDeleteShader(shaderId);
}

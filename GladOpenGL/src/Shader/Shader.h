#pragma once
#include "../Core.h"
#include <string>

class Shader
{
public:
	Shader(unsigned int shaderType) :shaderId(glCreateShader(shaderType)){}
	~Shader() {}

public:
	unsigned int shaderId{0};

public:
	void GetSourceAndCompile(std::string source);
	void DeleteShader();
};

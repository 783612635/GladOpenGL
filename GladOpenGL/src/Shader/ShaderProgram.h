#pragma once
#include "../Core.h"

class ShaderProgram
{
public:
	ShaderProgram():id(glCreateProgram()) {}
	~ShaderProgram() {}

public:
	unsigned int id{ 0 };

public:
	void AttachShader(unsigned int ShaderID) { glAttachShader(id, ShaderID); }
	void LinkProgarm() { glLinkProgram(id); }
	void DeleteProgram() { glDeleteProgram(id); }
};
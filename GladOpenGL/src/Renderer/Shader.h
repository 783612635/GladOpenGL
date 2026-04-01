#pragma once
#include "../Core.h"
#include <string>

class Shader
{
public:
	Shader(const char* VertexSPath, const char* FragmentSPath);
	~Shader() {}

public:
	unsigned int shaderProgramId{0};

public:
	void Use() const;
	void unUse() const { glUseProgram(0); }
	void GetSourceAndCompile(unsigned int ShaderID,const char* source);
	void CreateProgram(unsigned int vsID, unsigned int fsID);
	void DeleteShader();

	//Uniform
	void SetUniform1i(const std::string& name, int value) const;
	void SetUniform1f(const std::string& name, float value) const;
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

};

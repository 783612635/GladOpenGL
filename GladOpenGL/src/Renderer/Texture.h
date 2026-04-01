#pragma once
#include <GLAD/glad.h>

#include <string>

class Texture
{
public:
	Texture(const char* picPath, GLenum texType);
	~Texture() {}

	void Bind (unsigned int slot = 0) const;
	void UnBind() const;
	void Generate2DTex() const;

public:
	int width{0};
	int height{0};
	int nrChannels{0};
	unsigned int id{ 0 };
	unsigned char* data{ nullptr };
	unsigned int m_texType{ 0 };
	std::string texPath{};
};
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* picPath,  GLenum texType)
	:texPath(picPath),m_texType(texType)
{
	//垂直翻转纹理，因为OpenGL希望我们的纹理像素从左下角开始
	//openGL规定左下角为(0,0)
	stbi_set_flip_vertically_on_load(1);
	data = stbi_load(picPath, &width, &height, &nrChannels, 0);
	glGenTextures(1, &id);
	glBindTexture(m_texType, id);

	//指定缩小、放大过滤器，值得是需要渲染区域比纹理大小更小、或更大时，需要缩小或放大
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//设置水平或垂直嵌入环绕，我们不需要它扩大渲染区域
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	if (data)
	{
		Generate2DTex();
		stbi_image_free(data);
		data = nullptr;
	}
	UnBind();
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(m_texType, id);
}

void Texture::UnBind() const
{
	glBindTexture(m_texType, 0);
}

void Texture::Generate2DTex() const
{
	GLenum format = GL_RGB;
	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3)
		format = GL_RGB;
	else if (nrChannels == 4)
		format = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
}

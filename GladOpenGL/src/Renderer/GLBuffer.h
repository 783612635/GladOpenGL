#pragma once
#include "../Core.h"

class GLBuffer
{
public:
	//一对象一资源，方便维护，所以定死为1
	GLBuffer(GLenum types) :type(types) { glGenBuffers(1,&id); }
	~GLBuffer() { glDeleteBuffers(1, &id); }

	void Bind() const;
	void UnBind() const;

	void SetData(size_t size,const void* data,GLenum usage);

	GLuint GetID() const { return id; }

public:
	GLuint id{ 0 };
	GLenum type{ 0 };
};
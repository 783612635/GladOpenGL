#pragma once
#include <glad/glad.h>
#include "VertexLayout.h"
#include "GLBuffer.h"

class VertexArray
{
public:
	VertexArray() { glGenVertexArrays(1, &id); }
	~VertexArray() { glDeleteVertexArrays(1, &id); }

	void Bind() const;
	void UnBind() const;

	void AddBuffer(const GLBuffer& vbo, const VertexLayout& layout);

	void SetIndexBuffer(const GLBuffer& ebo);

	GLuint GetID() const { return id; };

public:
	GLuint id{ 0 };
};
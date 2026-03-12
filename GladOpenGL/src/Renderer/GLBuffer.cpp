#include "GLBuffer.h"
#include "VertexArray.h"

void GLBuffer::Bind() const
{
	glBindBuffer(type, id);
}

void GLBuffer::UnBind() const
{
	glBindBuffer(type, 0);
}

void GLBuffer::SetData(size_t size, const void* data, GLenum usage)
{
	Bind();
	glBufferData(type, size, data, usage);
}

#pragma once
#include <vector>
#include <glad/glad.h>

struct VertexAttribute
{
	GLuint index;
	GLint count;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
	size_t offset;
};

class VertexLayout
{
public:
    template<typename T>
    void Push(GLuint index, int count)
	{
		static_assert(sizeof(T) == 0);
	}

    template<>
    inline void Push<float>(GLuint index, int count)
    {
        VertexAttribute attr;

        attr.index = index;
        attr.count = count;
        attr.type = GL_FLOAT;
        attr.normalized = GL_FALSE;
        attr.offset = stride;

        stride += count * sizeof(float);
        attr.stride = stride;

        attributes.push_back(attr);
    }

    const std::vector<VertexAttribute>& GetAttributes() const { return attributes;}

	GLsizei GetStride() const { return stride; }
private:
    std::vector<VertexAttribute> attributes;
    GLsizei stride = 0;
};



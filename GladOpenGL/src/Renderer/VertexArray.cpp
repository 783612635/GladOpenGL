#include "VertexArray.h"

void VertexArray::Bind() const
{
	glBindVertexArray(id);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const GLBuffer& vbo, const VertexLayout& layout)
{
    Bind();
    vbo.Bind();

    const auto& attributes = layout.GetAttributes();

    for (const auto& attr : attributes)
    {
        glEnableVertexAttribArray(attr.index);

        glVertexAttribPointer(
            attr.index,
            attr.count,
            attr.type,
            attr.normalized,
            layout.GetStride(),
            (const void*)attr.offset
        );
    }
}

void VertexArray::SetIndexBuffer(const GLBuffer& ebo)
{
    Bind();
    ebo.Bind();
}
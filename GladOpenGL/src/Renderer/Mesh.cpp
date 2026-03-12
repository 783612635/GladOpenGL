#include "Mesh.h"

Mesh::Mesh(const void* vertices, size_t vertexSize, const unsigned int* indices, size_t indexSize, const VertexLayout& layout)
    :vbo(GL_ARRAY_BUFFER),
    ebo(GL_ELEMENT_ARRAY_BUFFER),
    indexCount(indexSize/sizeof(unsigned int))
{
    vao.Bind();

    vbo.SetData(vertexSize, vertices, GL_STATIC_DRAW);

    ebo.SetData(
        indexSize,
        indices,
        GL_STATIC_DRAW
    );

    vao.AddBuffer(vbo, layout);
    vao.SetIndexBuffer(ebo);
}

void Mesh::Draw() const
{
    vao.Bind();

    glDrawElements(
        GL_TRIANGLES,
        indexCount,
        GL_UNSIGNED_INT,
        nullptr
    );
}

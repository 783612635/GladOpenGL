#pragma once

#include "VertexArray.h"
#include "GLBuffer.h"

class Mesh
{
public:
    Mesh(
        const void* vertices,
        size_t vertexSize,
        const unsigned int* indices,
        size_t indexCount,
        const VertexLayout& layout
    );

    void DrawElements() const;
    void DrawArrays(unsigned int index,unsigned int counts) const;

    void UnBindVAO() const { vao.UnBind(); }

private:
    VertexArray vao;
    GLBuffer vbo;
    GLBuffer ebo;

    unsigned int indexCount;
};
#include "GLStateCache.h"

GLuint GLStateCache::currentVAO = 0;
GLuint GLStateCache::currentArrayBuffer = 0;
GLuint GLStateCache::currentElementBuffer = 0;
GLuint GLStateCache::currentProgram = 0;

void GLStateCache::BindVAO(GLuint vao)
{
    if (currentVAO == vao)
        return;

    glBindVertexArray(vao);
    currentVAO = vao;
}

void GLStateCache::BindArrayBuffer(GLuint vbo)
{
    if (currentArrayBuffer == vbo)
        return;

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    currentArrayBuffer = vbo;
}

void GLStateCache::BindElementBuffer(GLuint ebo)
{
    if (currentElementBuffer == ebo)
        return;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    currentElementBuffer = ebo;
}

void GLStateCache::UseProgram(GLuint program)
{
    if (currentProgram == program)
        return;

    glUseProgram(program);
    currentProgram = program;
}

void GLStateCache::Reset()
{
    currentVAO = 0;
    currentArrayBuffer = 0;
    currentElementBuffer = 0;
    currentProgram = 0;
}
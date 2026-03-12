#pragma once

#include <glad/glad.h>

class GLStateCache
{
public:

    static void BindVAO(GLuint vao);
    static void BindArrayBuffer(GLuint vbo);
    static void BindElementBuffer(GLuint ebo);
    static void UseProgram(GLuint program);

    static void Reset();

private:

    static GLuint currentVAO;
    static GLuint currentArrayBuffer;
    static GLuint currentElementBuffer;
    static GLuint currentProgram;
};
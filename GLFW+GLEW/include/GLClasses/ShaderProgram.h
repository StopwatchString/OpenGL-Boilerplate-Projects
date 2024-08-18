#ifndef GLCLASSES_SHADER_PROGRAM_H
#define GLCLASSES_SHADER_PROGRAM_H

#define GLEW_STATIC
#include "GL/glew.h"

#include <string>

class ShaderProgram
{
public:
    ShaderProgram(const char* vert_source, const char* frag_source);

    ~ShaderProgram();

    // No copying
    ShaderProgram(const ShaderProgram& other) = delete;
    ShaderProgram& operator=(const ShaderProgram& other) = delete;

    // Moving OK
    ShaderProgram(ShaderProgram&& other) noexcept;
    ShaderProgram& operator=(ShaderProgram&& other) noexcept;

    void bind();

    GLint getUniformLocation(const char* name);
    GLint getAttribLocation(const char* name);

private:
    GLuint m_Handle = 0;
};

#endif
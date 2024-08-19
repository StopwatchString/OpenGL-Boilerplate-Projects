#ifndef GLCLASSES_SHADER_PROGRAM_H
#define GLCLASSES_SHADER_PROGRAM_H

#define GLEW_STATIC
#include "GL/glew.h"

#include <string>

class ShaderProgram
{
public:
    ShaderProgram(const std::string& vertSourceFile, const std::string& fragSourceFile);

    ~ShaderProgram();

    // No copying
    ShaderProgram(const ShaderProgram& other) = delete;
    ShaderProgram& operator=(const ShaderProgram& other) = delete;

    // Moving OK
    ShaderProgram(ShaderProgram&& other) noexcept;
    ShaderProgram& operator=(ShaderProgram&& other) noexcept;

    void bind();
    void reloadShaders();

    GLint getUniformLocation(const char* name);
    GLint getAttribLocation(const char* name);

private:
    void createProgram();

    GLuint m_Handle = 0;
    const std::string m_VertexSourceFile;
    const std::string m_FragmentSourceFile;
};

#endif
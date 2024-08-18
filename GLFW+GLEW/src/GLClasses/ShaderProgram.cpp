#include "GLClasses/ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* vert_source, const char* frag_source)
{
    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vert_source, NULL);
    glCompileShader(vertex_shader);

    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &frag_source, NULL);
    glCompileShader(fragment_shader);

    m_Handle = glCreateProgram();
    glAttachShader(m_Handle, vertex_shader);
    glAttachShader(m_Handle, fragment_shader);
    glLinkProgram(m_Handle);
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_Handle);
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
{
    m_Handle = other.m_Handle;
    other.m_Handle = 0;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
{
    if (this != &other) {
        m_Handle = other.m_Handle;
        other.m_Handle = 0;
    }
    return *this;
}

void ShaderProgram::bind()
{
    glUseProgram(m_Handle);
}

GLint ShaderProgram::getUniformLocation(const char* name)
{
    return glGetUniformLocation(m_Handle, name);
}

GLint ShaderProgram::getAttribLocation(const char* name)
{
    return glGetAttribLocation(m_Handle, name);
}
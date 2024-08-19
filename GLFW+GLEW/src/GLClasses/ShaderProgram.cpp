#include "GLClasses/ShaderProgram.h"
#include "utils.h"

ShaderProgram::ShaderProgram(const std::string& vertSourceFile, const std::string& fragSourceFile)
    : m_VertexSourceFile(vertSourceFile)
    , m_FragmentSourceFile(fragSourceFile)
{
    createProgram();
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

void ShaderProgram::reloadShaders()
{
    createProgram();
}

GLint ShaderProgram::getUniformLocation(const char* name)
{
    return glGetUniformLocation(m_Handle, name);
}

GLint ShaderProgram::getAttribLocation(const char* name)
{
    return glGetAttribLocation(m_Handle, name);
}

void ShaderProgram::createProgram()
{
    if (m_Handle != 0) {
        glDeleteProgram(m_Handle);
        m_Handle = 0;
    }

    const char* vertSource = loadFile(m_VertexSourceFile);
    const char* fragSource = loadFile(m_FragmentSourceFile);


    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertSource, NULL);
    glCompileShader(vertex_shader);

    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragSource, NULL);
    glCompileShader(fragment_shader);

    m_Handle = glCreateProgram();
    glAttachShader(m_Handle, vertex_shader);
    glAttachShader(m_Handle, fragment_shader);
    glLinkProgram(m_Handle);
}
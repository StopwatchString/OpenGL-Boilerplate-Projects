#include "GLClasses/VAO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &m_Handle);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &m_Handle);
}

VAO::VAO(VAO&& other) noexcept
    : m_Handle(other.m_Handle)
{
    other.m_Handle = 0;
}

VAO& VAO::operator=(VAO&& other) noexcept
{
    if (this != &other) {
        m_Handle = other.m_Handle;
        other.m_Handle = 0;
    }
    return *this;
}

void VAO::bind()
{
    glBindVertexArray(m_Handle);
}

void VAO::specifyAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
    glBindVertexArray(m_Handle);
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glBindVertexArray(0);
}
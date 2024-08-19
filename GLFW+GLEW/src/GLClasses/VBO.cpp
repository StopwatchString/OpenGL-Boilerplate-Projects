#include "GLClasses/VBO.h"
#include <assert.h>

VBO::VBO()
{
    glGenBuffers(1, &m_Handle);
}

VBO::~VBO()
{
    glDeleteBuffers(1, &m_Handle);
}

VBO::VBO(VBO&& other) noexcept
{
    m_Handle = other.m_Handle;
    m_Size = other.m_Size;
    m_Usage = other.m_Usage;
    m_Allocated = other.m_Allocated;

    other.m_Handle = 0;
    other.m_Size = 0;
    other.m_Usage = 0;
    other.m_Allocated = false;
}

VBO& VBO::operator=(VBO&& other) noexcept
{
    if (this != &other) {
        m_Handle = other.m_Handle;
        m_Size = other.m_Size;
        m_Usage = other.m_Usage;
        m_Allocated = other.m_Allocated;

        other.m_Handle = 0;
        other.m_Size = 0;
        other.m_Usage = 0;
        other.m_Allocated = false;
    }
    return *this;
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
}

void VBO::allocate(GLsizeiptr size, const void* data, GLenum usage)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_Handle);

    m_Size = size;
    m_Usage = usage;

    glBufferData(GL_ARRAY_BUFFER, size, data, usage);

    m_Allocated = true;
}

void VBO::update(GLintptr offset, GLsizeiptr size, const void* data)
{
#ifndef NDEBUG
    assert(m_Allocated);
    assert((offset + size) <= m_Size);
#endif
    glBindBuffer(GL_ARRAY_BUFFER, m_Handle);

    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}
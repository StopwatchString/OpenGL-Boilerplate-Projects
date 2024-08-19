#include "GLClasses/IBO.h"

IBO::IBO()
{
    glGenBuffers(1, &m_Handle);
}

IBO::~IBO()
{
    glDeleteBuffers(1, &m_Handle);
}

IBO::IBO(IBO&& other) noexcept
    : m_Handle(other.m_Handle)
    , m_Size(other.m_Size)
    , m_Usage(other.m_Usage)
    , m_Allocated(other.m_Allocated)
{
    other.m_Handle = 0;
    other.m_Size = 0;
    other.m_Usage = 0;
    other.m_Allocated = false;
}

IBO& IBO::operator=(IBO&& other) noexcept
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

void IBO::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle);
}

void IBO::allocate(GLsizeiptr size, const void* data, GLenum usage)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);

    m_Size = size;
    m_Usage = usage;
    m_Allocated = true;
}

void IBO::update(GLintptr offset, GLsizeiptr size, const void* data)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle);

    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}
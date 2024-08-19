#ifndef GLCLASSES_UBO_H
#define GLCLASSES_UBO_H

#define GLEW_STATIC
#include "GL/glew.h"

#include <utility>

template<typename _DataType>
class UBO
{
public:
    UBO(GLuint bindingPoint)
        : m_BindingPoint(bindingPoint)
    {
        glGenBuffers(1, &m_Handle);
        glBindBuffer(GL_UNIFORM_BUFFER, m_Handle);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(_DataType), NULL, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, m_BindingPoint, m_Handle);

        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    ~UBO()
    {
        glDeleteBuffers(1, &m_Handle);
    }

    // No copying
    UBO(const UBO<_DataType>& other) = delete;
    UBO<_DataType>& operator=(const UBO<_DataType>& other) = delete;
    
    // Moving OK
    UBO(UBO<_DataType>&& other) noexcept
        : m_Data(std::move(other.m_Data()))
        , m_BindingPoint(other.m_BindingPoint)
    {
        glDeleteBuffers(1, &m_Handle);
        m_Handle = other.m_Handle;

        other.m_BindingPoint = 0;
        other.m_Handle = 0;
    };

    UBO& operator=(UBO<_DataType>&& other) noexcept
    {
        if (this != &other) {
            glDeleteBuffers(1, &m_Handle);

            m_Data = std::move(other.m_Data);
            m_BindingPoint = other.m_BindingPoint;
            m_Handle = other.m_Handle;

            other.m_BindingPoint = 0;
            other.m_Handle = 0;
        }
        return *this;
    };

    _DataType* operator->() const
    {
        return &m_Data;
    };

    _DataType* data() { return &m_Data; }
    GLuint handle() { return m_Handle; }
    
    void uploadData()
    {
        glBindBuffer(GL_UNIFORM_BUFFER, m_Handle);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(_DataType), &m_Data);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    };

private:
    _DataType m_Data;
    GLint m_BindingPoint = 0;
    GLuint m_Handle = 0;
};

#endif
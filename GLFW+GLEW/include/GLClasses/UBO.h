#ifndef GLCLASSES_UBO_H
#define GLCLASSES_UBO_H

#define GLEW_STATIC
#include "GL/glew.h"

#include <utility>

template<typename _DataType>
class UBO
{
public:
    UBO(GLint location)
    {
        m_Location = location;

        glGenBuffers(1, &m_Handle);
        glBindBuffer(GL_UNIFORM_BUFFER, m_Handle);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(_DataType), NULL, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, m_Location, m_Handle);

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
    {
        m_Data = std::move(other.m_Data);
        m_Location = other.m_Location;

        other.m_Location = 0;
    };

    UBO& operator=(UBO<_DataType>&& other) noexcept
    {
        if (this != &other) {
            m_Data = std::move(other.m_Data);
            m_Location = other.m_Location;

            other.m_Location = 0;
        }
        return *this;
    };

    _DataType* operator->() const
    {
        return &m_Data;
    };

    _DataType* data() { return &m_Data; }
    
    void uploadData()
    {
        glBindBuffer(GL_UNIFORM_BUFFER, m_Handle);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(_DataType), &m_Data);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    };

private:
    _DataType m_Data;
    GLint m_Location = 0;
    GLuint m_Handle = 0;
};

#endif
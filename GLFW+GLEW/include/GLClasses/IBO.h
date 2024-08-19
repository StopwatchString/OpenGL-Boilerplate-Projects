#ifndef GLCLASSES_IBO_H
#define GLCLASSES_IBO_H

#define GLEW_STATIC
#include "GL/glew.h"

class IBO
{
public:
    IBO();
    ~IBO();
    // No copying
    IBO(const IBO& other) = delete;
    IBO& operator=(const IBO& other) = delete;
    // Moving OK
    IBO(IBO&& other) noexcept;
    IBO& operator=(IBO&& other) noexcept;

    void bind();
    void allocate(GLsizeiptr size, const void* data, GLenum usage);
    void update(GLintptr offset, GLsizeiptr size, const void* data);

    GLuint handle() { return m_Handle; }
    GLsizeiptr size() { return m_Size; }
    GLenum usage() { return m_Usage; }

private:
    GLuint m_Handle = 0;
    GLsizeiptr m_Size = 0;
    GLenum m_Usage = 0;
    bool m_Allocated = false;
};

#endif
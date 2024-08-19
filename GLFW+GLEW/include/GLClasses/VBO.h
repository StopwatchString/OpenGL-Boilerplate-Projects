#ifndef GLCLASSES_VBO_H
#define GLCLASSES_VBO_H

#define GLEW_STATIC
#include "GL/glew.h"

class VBO
{
public:
    VBO();
    ~VBO();
    // No copying
    VBO(const VBO& other) = delete;
    VBO& operator=(const VBO& other) = delete;
    // Moving OK
    VBO(VBO&& other) noexcept;
    VBO& operator=(VBO&& other) noexcept;

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
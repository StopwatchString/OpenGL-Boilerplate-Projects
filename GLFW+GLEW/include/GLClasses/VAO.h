#ifndef GLCLASSES_VAO_H
#define GLCLASSES_VAO_H

#define GLEW_STATIC
#include "GL/glew.h"

class VAO
{
public:
    VAO();
    ~VAO();
    // No copying
    VAO(const VAO& other) = delete;
    VAO& operator=(const VAO& other) = delete;
    // Moving OK
    VAO(VAO&& other) noexcept;
    VAO& operator=(VAO&& other) noexcept;

    void bind();
    void specifyAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

private:
    GLuint m_Handle = 0;;
};

#endif
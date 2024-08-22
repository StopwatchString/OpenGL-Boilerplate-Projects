#ifndef GLH_VBO_H
#define GLH_VBO_H

#define GLEW_STATIC
#include "GL/glew.h"

namespace glh {
    namespace VBO {
        void create(GLuint& VBO);
        void create(GLsizei num, GLuint* VBOArray);

        void destroy(GLuint& VBO);
        void destroy(GLsizei num, GLuint* VBOArray);

        void bind(GLuint VBO);

        void allocateBuffer(GLsizeiptr size, const void* data, GLenum usage, GLuint expectedBoundVBO = 0);
        void updateBuffer(GLintptr offset, GLsizeiptr size, const void* data, GLuint expectedBoundVBO = 0);
    }
}

#endif
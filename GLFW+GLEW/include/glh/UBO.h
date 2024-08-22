#ifndef GLH_UBO_H
#define GLH_UBO_H

#define GLEW_STATIC
#include "GL/glew.h"

namespace glh {
    namespace UBO {
        void create(GLuint& UBO);
        void create(GLsizei num, GLuint* UBOArray);

        void destroy(GLuint& UBO);
        void destroy(GLsizei num, GLuint* UBOArray);

        void bind(GLuint UBO);

        void allocateBuffer(GLsizeiptr size, const void* data, GLenum usage, GLuint expectedBoundUBO = 0);
        void updateBuffer(GLintptr offset, GLsizeiptr size, const void* data, GLuint expectedBoundUBO = 0);

        void bindBufferBase(GLuint bindingPoint, GLuint UBO);
    }
}

#endif
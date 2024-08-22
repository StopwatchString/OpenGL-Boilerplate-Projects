#ifndef GLH_VAO_H
#define GLH_VAO_H

#define GLEW_STATIC
#include "GL/glew.h"

namespace glh {
    namespace VAO {
        void create(GLuint& VAO);
        void create(GLsizei num, GLuint* VAOArray);

        void destroy(GLuint& VAO);
        void destroy(GLsizei num, GLuint* VAOArray);
        
        void bind(GLuint VAO);
        
        void enableVertexAttribArray(GLuint index, GLuint expectedBoundVAO = 0);
        void disableVertexAttribArray(GLuint index, GLuint expectedBoundVAO = 0);
        void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer, GLuint expectedBoundVAO = 0);
    }
}

#endif
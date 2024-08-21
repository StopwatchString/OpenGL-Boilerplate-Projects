#ifndef GLTK_VAO_H
#define GLTK_VAO_H

#define GLEW_STATIC
#include "GL/glew.h"

namespace gltk {
    namespace VAO {
        inline void create(GLuint& VAO);
        inline void create(GLsizei num, GLuint* VAOArray);

        inline void destroy(GLuint& VAO);
        inline void destroy(GLsizei num, GLuint* VAOArray);
        
        inline void bind(GLuint VAO);
        
        inline void enableVertexAttribArray(GLuint index, GLuint expectedBoundVAO = 0);
        inline void disableVertexAttribArray(GLuint index, GLuint expectedBoundVAO = 0);
        inline void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer, GLuint expectedBoundVAO = 0);
    }
}

#endif
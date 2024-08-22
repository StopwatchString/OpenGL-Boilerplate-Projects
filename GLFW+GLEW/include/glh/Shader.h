#ifndef GLH_SHADER_H
#define GLH_SHADER_H

#define GLEW_STATIC
#include "GL/glew.h"

namespace glh {
    namespace shader {
        // Valid Shader Types:
        // GL_COMPUTE_SHADER
        // GL_VERTEX_SHADER
        // GL_TESS_CONTROL_SHADER
        // GL_TESS_EVALUATION_SHADER
        // GL_GEOMETRY_SHADER
        // GL_FRAGMENT_SHADER
        GLuint create(GLenum shaderType);

        void destroy(GLuint shader);

        void attachSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);

        void compileShader(GLuint shader);

        bool isCompiled(GLuint shader);
    }
}

#endif
#ifndef GLTK_SHADER_PROGRAM_H
#define GLTK_SHADER_PROGRAM_H

#define GLEW_STATIC
#include "GL/glew.h"

namespace gltk {
    namespace ShaderProgram {
        void create(GLuint& shaderProgramHandle, const char* vertexSource, const char* fragmentSource);

        void destroy(GLuint& shaderProgramHandle);

        void bind(GLuint shaderProgramHandle);
    }
}

#endif
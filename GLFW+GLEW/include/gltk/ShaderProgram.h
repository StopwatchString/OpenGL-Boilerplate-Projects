#ifndef GLHELPERS_SHADER_PROGRAM_H
#define GLHELPERS_SHADER_PROGRAM_H

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
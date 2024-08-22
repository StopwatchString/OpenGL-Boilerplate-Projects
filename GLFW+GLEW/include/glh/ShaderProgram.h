#ifndef GLH_SHADER_PROGRAM_H
#define GLH_SHADER_PROGRAM_H

#define GLEW_STATIC
#include "GL/glew.h"

namespace glh {
    namespace ShaderProgram {
        void create(GLuint& shaderProgramHandle, const char* vertexSource, const char* fragmentSource);

        void destroy(GLuint& shaderProgramHandle);

        void bind(GLuint shaderProgramHandle);
    }
}

#endif
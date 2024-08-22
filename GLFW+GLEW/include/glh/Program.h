#ifndef GLH_PROGRAM_H
#define GLH_PROGRAM_H

#define GLEW_STATIC
#include "GL/glew.h"

namespace glh {
    namespace program {
        GLuint create();

        void destroy(GLuint& program);

        void bind(GLuint program);

        void attachShader(GLuint program, GLuint shader);
        void detachShader(GLuint program, GLuint shader);

        void linkProgram(GLuint program);
    }
}

#endif
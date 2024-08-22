#include "glh/Program.h"
#include "glh/macros.h"

namespace glh {
    namespace program {
        GLuint create() {
            GL_ERROR_CHECK("program", "create", "Prexisting");

            GLuint program = glCreateProgram();
            GL_ERROR_CHECK("program", "create", "glCreateProgram");

            return program;
        }

        void destroy(GLuint& program) {
            GL_ERROR_CHECK("program", "destroy", "Prexisting");

            glDeleteProgram(program);
            GL_ERROR_CHECK("program", "destroy", "glDeleteProgram");
        }

        void bind(GLuint program) {
            GL_ERROR_CHECK("program", "bind", "Prexisting");

            glUseProgram(program);
            GL_ERROR_CHECK("program", "bind", "glUseProgram");
        }

        void attachShader(GLuint program, GLuint shader) {
            GL_ERROR_CHECK("program", "attachShader", "Prexisting");

            glAttachShader(program, shader);
            GL_ERROR_CHECK("program", "attachShader", "glAttachShader");
        }

        void detachShader(GLuint program, GLuint shader) {
            GL_ERROR_CHECK("program", "detachShader", "Prexisting");

            glDetachShader(program, shader);
            GL_ERROR_CHECK("program", "detachShader", "glDetachShader");
        }

        void linkProgram(GLuint program) {
            GL_ERROR_CHECK("program", "linkProgram", "Prexisting");

            glLinkProgram(program);
            GL_ERROR_CHECK("program", "linkProgram", "glLinkProgram");
        }
    }
}
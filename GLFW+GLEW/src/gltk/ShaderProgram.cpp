#include "gltk/ShaderProgram.h"

#include <iostream>

namespace gltk {
    namespace ShaderProgram {
        void create(GLuint& shaderProgramHandle, const char* vertexSource, const char* fragmentSource) {
            const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex_shader, 1, &vertexSource, NULL);
            glCompileShader(vertex_shader);

            const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment_shader, 1, &fragmentSource, NULL);
            glCompileShader(fragment_shader);

            shaderProgramHandle = glCreateProgram();
            glAttachShader(shaderProgramHandle, vertex_shader);
            glAttachShader(shaderProgramHandle, fragment_shader);
            glLinkProgram(shaderProgramHandle);
        }

        void destroy(GLuint& shaderProgramHandle) {
            glDeleteProgram(shaderProgramHandle);
        }

        void bind(GLuint shaderProgramHandle) {
            glUseProgram(shaderProgramHandle);
        }
    }
}
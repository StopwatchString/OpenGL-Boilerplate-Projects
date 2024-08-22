#include "glh/VAO.h"
#include "glh/macros.h"

#include <iostream>

#ifndef NDEBUG
class DebugInfoVAO {
public:
    static DebugInfoVAO* getInstance() {
        if (instance == nullptr) {
            instance = new DebugInfoVAO();
        }
        return instance;
    }

    GLuint currentlyBoundVAO;

private:
    static DebugInfoVAO* instance;

    DebugInfoVAO() : currentlyBoundVAO(0) {}
    DebugInfoVAO(const DebugInfoVAO&) = delete;
    DebugInfoVAO& operator=(const DebugInfoVAO&) = delete;
};

DebugInfoVAO* DebugInfoVAO::instance = nullptr;

static DebugInfoVAO* debugInfoVAO = DebugInfoVAO::getInstance();

#define VERIFY_BOUND_VAO(expectedBoundVAO, funcName)                                       \
do {                                                                                       \
    if (expectedBoundVAO == 0) continue;                                                   \
    if (expectedBoundVAO != debugInfoVAO->currentlyBoundVAO) {                             \
        std::cerr << "glh::VAO::" << funcName << "()"                                      \
            << " VAO expected=" <<  expectedBoundVAO                                       \
            << " VAO current=" << debugInfoVAO->currentlyBoundVAO << '\n';                 \
    }                                                                                      \
} while(0)

#define TRACK_BOUND_VAO(newVAO) debugInfoVAO->currentlyBoundVAO = newVAO

#else

#define VERIFY_BOUND_VAO(expectedBoundVAO, funcName)
#define TRACK_BOUND_VAO(newVAO)

#endif

namespace glh {
    namespace VAO {
        void create(GLuint& VAO) {
            GL_ERROR_CHECK("VAO", "create", "Prexisting");

            glGenVertexArrays(1, &VAO);
            GL_ERROR_CHECK("VAO", "create", "glGenVertexArrays");
        }

        void create(GLsizei num, GLuint* VAOArray) {
            GL_ERROR_CHECK("VAO", "create", "Prexisting");

            glGenVertexArrays(num, VAOArray);
            GL_ERROR_CHECK("VAO", "create", "glGenVertexArrays");
        }

        void destroy(GLuint& VAO) {
            GL_ERROR_CHECK("VAO", "destroy", "Prexisting");

            glDeleteVertexArrays(1, &VAO);
            GL_ERROR_CHECK("VAO", "destroy", "glDeleteVertexArrays");
        }

        void destroy(GLsizei num, GLuint* VAOArray) {
            GL_ERROR_CHECK("VAO", "destroy", "Prexisting");

            glDeleteVertexArrays(num, VAOArray);
            GL_ERROR_CHECK("VAO", "destroy", "glDeleteVertexArrays");
        }

        void bind(GLuint VAO) {
            GL_ERROR_CHECK("VAO", "bind", "Prexisting");
            TRACK_BOUND_VAO(VAO);

            glBindVertexArray(VAO);
            GL_ERROR_CHECK("VAO", "bind", "glBindVertexArray");
        }

        void enableVertexAttribArray(GLuint index, GLuint expectedBoundVAO) {
            GL_ERROR_CHECK("VAO", "enableVertexAttribArray", "Prexisting");
            VERIFY_BOUND_VAO(expectedBoundVAO, "enableVertexAttribArray");

            glEnableVertexAttribArray(index);
            GL_ERROR_CHECK("VAO", "enableVertexAttribArray", "glEnableVertexAttribArray");
        }

        void disableVertexAttribArray(GLuint index, GLuint expectedBoundVAO) {
            GL_ERROR_CHECK("VAO", "disableVertexAttribArray", "Prexisting");
            VERIFY_BOUND_VAO(expectedBoundVAO, "disableVertexAttribArray");

            glDisableVertexAttribArray(index);
            GL_ERROR_CHECK("VAO", "disableVertexAttribArray", "glDisableVertexAttribArray");
        }

        void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer, GLuint expectedBoundVAO) {
            GL_ERROR_CHECK("VAO", "vertexAttribPointer", "Prexisting");
            VERIFY_BOUND_VAO(expectedBoundVAO, "vertexAttribPointer");

            glVertexAttribPointer(index, size, type, normalized, stride, pointer);
            GL_ERROR_CHECK("VAO", "vertexAttribPointer", "glVertexAttribPointer");
        }
    }
}
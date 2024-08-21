#include "gltk/VAO.h"

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
        std::cerr << "gltk::VAO::" << funcName << "()"                                     \
            << " VAO expected=" <<  expectedBoundVAO                                       \
            << " VAO current=" << debugInfoVAO->currentlyBoundVAO << '\n';                 \
    }                                                                                      \
} while(0)

#define TRACK_BOUND_VAO(newVAO) debugInfoVAO->currentlyBoundVAO = newVAO

#else

#define VERIFY_BOUND_VAO(expectedBoundVAO, funcName)
#define TRACK_BOUND_VAO(newVAO)

#endif

namespace gltk {
    namespace VAO {
        void create(GLuint& VAO) {
            glGenVertexArrays(1, &VAO);
        }

        void create(GLsizei num, GLuint* VAOArray) {
            glGenVertexArrays(num, VAOArray);
        }

        void destroy(GLuint& VAO) {
            glDeleteVertexArrays(1, &VAO);
        }

        void destroy(GLsizei num, GLuint* VAOArray) {
            glDeleteVertexArrays(num, VAOArray);
        }

        void bind(GLuint VAO) {
            TRACK_BOUND_VAO(VAO);

            glBindVertexArray(VAO);
        }

        void enableVertexAttribArray(GLuint index, GLuint expectedBoundVAO) {
            VERIFY_BOUND_VAO(expectedBoundVAO, "enableVertexAttribArray");

            glEnableVertexAttribArray(index);
        }

        void disableVertexAttribArray(GLuint index, GLuint expectedBoundVAO) {
            VERIFY_BOUND_VAO(expectedBoundVAO, "disableVertexAttribArray");

            glDisableVertexAttribArray(index);
        }

        void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer, GLuint expectedBoundVAO) {
            VERIFY_BOUND_VAO(expectedBoundVAO, "vertexAttribPointer");

            glVertexAttribPointer(index, size, type, normalized, stride, pointer);
        }
    }
}
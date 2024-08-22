#include "glh/VBO.h"

#include <iostream>

#ifndef NDEBUG
class DebugInfoVBO {
public:
    static DebugInfoVBO* getInstance() {
        if (instance == nullptr) {
            instance = new DebugInfoVBO();
        }
        return instance;
    }

    GLuint currentlyBoundVBO;

private:
    static DebugInfoVBO* instance;

    DebugInfoVBO() : currentlyBoundVBO(0) {}
    DebugInfoVBO(const DebugInfoVBO&) = delete;
    DebugInfoVBO& operator=(const DebugInfoVBO&) = delete;
};

DebugInfoVBO* DebugInfoVBO::instance = nullptr;

static DebugInfoVBO* debugInfoVBO = DebugInfoVBO::getInstance();

#define VERIFY_BOUND_VBO(expectedBoundVBO, funcName)                                       \
do {                                                                                       \
    if (expectedBoundVBO == 0) continue;                                                   \
    if (expectedBoundVBO != debugInfoVBO->currentlyBoundVBO) {                             \
        std::cerr << "glh::VBO::" << funcName << "()"                                     \
            << " VBO expected=" <<  expectedBoundVBO                                       \
            << " VBO current=" << debugInfoVBO->currentlyBoundVBO << '\n';                 \
    }                                                                                      \
} while(0)

#define TRACK_BOUND_VBO(newVBO) debugInfoVBO->currentlyBoundVBO = newVBO

#else

#define VERIFY_BOUND_VBO(expectedBoundVBO, funcName)
#define TRACK_BOUND_VBO(newVBO)

#endif

namespace glh {
    namespace VBO {
        void create(GLuint& VBO) {
            glGenBuffers(1, &VBO);
        }

        void create(GLsizei num, GLuint* VBOArray) {
            glGenBuffers(num, VBOArray);
        }

        void destroy(GLuint& VBO) {
            glDeleteBuffers(1, &VBO);
        }

        void destroy(GLsizei num, GLuint* VBOArray) {
            glDeleteBuffers(num, VBOArray);
        }

        void bind(GLuint VBO) {
            TRACK_BOUND_VBO(VBO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
        }

        void allocateBuffer(GLsizeiptr size, const void* data, GLenum usage, GLuint expectedBoundVBO) {
            VERIFY_BOUND_VBO(expectedBoundVBO, "allocateBuffer");

            glBufferData(GL_ARRAY_BUFFER, size, data, usage);
        }

        void updateBuffer(GLintptr offset, GLsizeiptr size, const void* data, GLuint expectedBoundVBO) {
            VERIFY_BOUND_VBO(expectedBoundVBO, "updateBuffer");

            glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
        }
    }
}
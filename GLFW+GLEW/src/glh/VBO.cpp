#include "glh/VBO.h"
#include "glh/macros.h"

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
        std::cerr << "glh::VBO::" << funcName << "()"                                      \
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
            GL_ERROR_CHECK("VBO", "create", "Prexisting");

            glGenBuffers(1, &VBO);
            GL_ERROR_CHECK("VBO", "create", "glGenBuffers");
        }

        void create(GLsizei num, GLuint* VBOArray) {
            GL_ERROR_CHECK("VBO", "create", "Prexisting");

            glGenBuffers(num, VBOArray);
            GL_ERROR_CHECK("VBO", "create", "glGenBuffers");
        }

        void destroy(GLuint& VBO) {
            GL_ERROR_CHECK("VBO", "destroy", "Prexisting");

            glDeleteBuffers(1, &VBO);
            GL_ERROR_CHECK("VBO", "destroy", "glDeleteBuffers");
        }

        void destroy(GLsizei num, GLuint* VBOArray) {
            GL_ERROR_CHECK("VBO", "destroy", "Prexisting");

            glDeleteBuffers(num, VBOArray);
            GL_ERROR_CHECK("VBO", "destroy", "glDeleteBuffers");
        }

        void bind(GLuint VBO) {
            GL_ERROR_CHECK("VBO", "bind", "Prexisting");
            TRACK_BOUND_VBO(VBO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            GL_ERROR_CHECK("VBO", "bind", "glBindBuffer");
        }

        void allocateBuffer(GLsizeiptr size, const void* data, GLenum usage, GLuint expectedBoundVBO) {
            GL_ERROR_CHECK("VBO", "allocateBuffer", "Prexisting");
            VERIFY_BOUND_VBO(expectedBoundVBO, "allocateBuffer");

            glBufferData(GL_ARRAY_BUFFER, size, data, usage);
            GL_ERROR_CHECK("VBO", "allocateBuffer", "glBufferData");
        }

        void updateBuffer(GLintptr offset, GLsizeiptr size, const void* data, GLuint expectedBoundVBO) {
            GL_ERROR_CHECK("VBO", "updateBuffer", "Prexisting");
            VERIFY_BOUND_VBO(expectedBoundVBO, "updateBuffer");

            glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
            GL_ERROR_CHECK("VBO", "updateBuffer", "glBufferSubData");
        }
    }
}
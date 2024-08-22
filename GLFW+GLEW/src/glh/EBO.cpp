#include "glh/EBO.h"
#include "glh/macros.h"

#include <iostream>

#ifndef NDEBUG
class DebugInfoEBO {
public:
    static DebugInfoEBO* getInstance() {
        if (instance == nullptr) {
            instance = new DebugInfoEBO();
        }
        return instance;
    }

    GLuint currentlyBoundEBO;

private:
    static DebugInfoEBO* instance;

    DebugInfoEBO() : currentlyBoundEBO(0) {}
    DebugInfoEBO(const DebugInfoEBO&) = delete;
    DebugInfoEBO& operator=(const DebugInfoEBO&) = delete;
};

DebugInfoEBO* DebugInfoEBO::instance = nullptr;

static DebugInfoEBO* debugInfoEBO = DebugInfoEBO::getInstance();

#define VERIFY_BOUND_EBO(expectedBoundEBO, funcName)                                       \
do {                                                                                       \
    if (expectedBoundEBO == 0) continue;                                                   \
    if (expectedBoundEBO != debugInfoEBO->currentlyBoundEBO) {                             \
        std::cerr << "glh::EBO::" << funcName << "()"                                     \
            << " EBO expected=" <<  expectedBoundEBO                                       \
            << " EBO current=" << debugInfoEBO->currentlyBoundEBO << '\n';                 \
    }                                                                                      \
} while(0)

#define TRACK_BOUND_EBO(newEBO) debugInfoEBO->currentlyBoundEBO = newEBO

#else

#define VERIFY_BOUND_EBO(expectedBoundEBO, funcName)
#define TRACK_BOUND_EBO(newEBO)

#endif

namespace glh {
    namespace EBO {
        void create(GLuint& EBO) {
            GL_ERROR_CHECK("EBO", "create", "Prexisting");

            glGenBuffers(1, &EBO);

            GL_ERROR_CHECK("EBO", "create", "glGenBuffers");
        }

        void create(GLsizei num, GLuint* EBOArray) {
            GL_ERROR_CHECK("EBO", "create", "Prexisting");

            glGenBuffers(num, EBOArray);

            GL_ERROR_CHECK("EBO", "create", "glGenBuffers");
        }

        void destroy(GLuint& EBO) {
            GL_ERROR_CHECK("EBO", "destroy", "Prexisting");

            glDeleteBuffers(1, &EBO);

            GL_ERROR_CHECK("EBO", "destroy", "glDeleteBuffers");
        }

        void destroy(GLsizei num, GLuint* EBOArray) {
            GL_ERROR_CHECK("EBO", "destroy", "Prexisting");

            glDeleteBuffers(num, EBOArray);

            GL_ERROR_CHECK("EBO", "destroy", "glDeleteBuffers");
        }

        void bind(GLuint EBO) {
            GL_ERROR_CHECK("EBO", "bind", "Prexisting");
            TRACK_BOUND_EBO(EBO);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

            GL_ERROR_CHECK("EBO", "bind", "glBindBuffer");
        }

        void allocateBuffer(GLsizeiptr size, const void* data, GLenum usage, GLuint expectedBoundEBO) {
            GL_ERROR_CHECK("EBO", "allocateBuffer", "Prexisting");
            VERIFY_BOUND_EBO(expectedBoundEBO, "allocateBuffer");

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);

            GL_ERROR_CHECK("EBO", "allocateBuffer", "glBufferData");
        }

        void updateBuffer(GLintptr offset, GLsizeiptr size, const void* data, GLuint expectedBoundEBO) {
            GL_ERROR_CHECK("EBO", "updateBuffer", "Prexisting");
            VERIFY_BOUND_EBO(expectedBoundEBO, "updateBuffer");

            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);

            GL_ERROR_CHECK("EBO", "updateBuffer", "glBufferSubData");
        }
    }
}
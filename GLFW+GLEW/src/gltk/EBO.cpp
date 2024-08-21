#include "gltk/EBO.h"

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
        std::cerr << "gltk::EBO::" << funcName << "()"                                     \
            << " EBO expected=" <<  expectedBoundEBO                                       \
            << " EBO current=" << debugInfoEBO->currentlyBoundEBO << '\n';                 \
    }                                                                                      \
} while(0)

#define TRACK_BOUND_EBO(newEBO) debugInfoEBO->currentlyBoundEBO = newEBO

#else

#define VERIFY_BOUND_EBO(expectedBoundEBO, funcName)
#define TRACK_BOUND_EBO(newEBO)

#endif

namespace gltk {
    namespace EBO {
        void create(GLuint& EBO) {
            glGenBuffers(1, &EBO);
        }

        void create(GLsizei num, GLuint* EBOArray) {
            glGenBuffers(num, EBOArray);
        }

        void destroy(GLuint& EBO) {
            glDeleteBuffers(1, &EBO);
        }

        void destroy(GLsizei num, GLuint* EBOArray) {
            glDeleteBuffers(num, EBOArray);
        }

        void bind(GLuint EBO) {
            TRACK_BOUND_EBO(EBO);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        }

        void allocateBuffer(GLsizeiptr size, const void* data, GLenum usage, GLuint expectedBoundEBO) {
            VERIFY_BOUND_EBO(expectedBoundEBO, "allocateBuffer");

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
        }

        void updateBuffer(GLintptr offset, GLsizeiptr size, const void* data, GLuint expectedBoundEBO) {
            VERIFY_BOUND_EBO(expectedBoundEBO, "updateBuffer");

            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
        }
    }
}
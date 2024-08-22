#include "glh/UBO.h"
#include "glh/macros.h"

#include <iostream>

#ifndef NDEBUG
class DebugInfoUBO {
public:
    static DebugInfoUBO* getInstance() {
        if (instance == nullptr) {
            instance = new DebugInfoUBO();
        }
        return instance;
    }

    GLuint currentlyBoundUBO;

private:
    static DebugInfoUBO* instance;

    DebugInfoUBO() : currentlyBoundUBO(0) {}
    DebugInfoUBO(const DebugInfoUBO&) = delete;
    DebugInfoUBO& operator=(const DebugInfoUBO&) = delete;
};

DebugInfoUBO* DebugInfoUBO::instance = nullptr;

static DebugInfoUBO* debugInfoUBO = DebugInfoUBO::getInstance();

#define VERIFY_BOUND_UBO(expectedBoundUBO, funcName)                        \
do {                                                                        \
    if (expectedBoundUBO == 0) continue;                                    \
    if (expectedBoundUBO != debugInfoUBO->currentlyBoundUBO) {              \
        std::cerr << "glh::UBO::" << funcName << "()"                       \
            << " UBO expected=" <<  expectedBoundUBO                        \
            << " UBO current=" << debugInfoUBO->currentlyBoundUBO << '\n';  \
    }                                                                       \
} while(0)

#define TRACK_BOUND_UBO(newUBO) debugInfoUBO->currentlyBoundUBO = newUBO

#else

#define VERIFY_BOUND_UBO(expectedBoundUBO, funcName)
#define TRACK_BOUND_UBO(newUBO)

#endif

namespace glh {
    namespace UBO {
        void create(GLuint& UBO) {
            GL_ERROR_CHECK("UBO", "create", "Prexisting");

            glGenBuffers(1, &UBO);

            GL_ERROR_CHECK("UBO", "create", "glGenBuffers");
        }

        void create(GLsizei num, GLuint* UBOArray) {
            GL_ERROR_CHECK("UBO", "create", "Prexisting");

            glGenBuffers(num, UBOArray);

            GL_ERROR_CHECK("UBO", "create", "glGenBuffers");
        }

        void destroy(GLuint& UBO) {
            GL_ERROR_CHECK("UBO", "destroy", "Prexisting");

            glDeleteBuffers(1, &UBO);

            GL_ERROR_CHECK("UBO", "destroy", "glDeleteBuffers");
        }

        void destroy(GLsizei num, GLuint* UBOArray) {
            GL_ERROR_CHECK("UBO", "destroy", "Prexisting");

            glDeleteBuffers(num, UBOArray);

            GL_ERROR_CHECK("UBO", "destroy", "glDeleteBuffers");
        }

        void bind(GLuint UBO) {
            GL_ERROR_CHECK("UBO", "bind", "Prexisting");
            TRACK_BOUND_UBO(UBO);

            glBindBuffer(GL_UNIFORM_BUFFER, UBO);

            GL_ERROR_CHECK("UBO", "bind", "glBindBuffer");
        }

        void allocateBuffer(GLsizeiptr size, const void* data, GLenum usage, GLuint expectedBoundUBO) {
            GL_ERROR_CHECK("UBO", "allocateBuffer", "Prexisting");
            VERIFY_BOUND_UBO(expectedBoundUBO, "allocateBuffer");

            glBufferData(GL_UNIFORM_BUFFER, size, data, usage);

            GL_ERROR_CHECK("UBO", "allocateBuffer", "glBufferData");
        }

        void updateBuffer(GLintptr offset, GLsizeiptr size, const void* data, GLuint expectedBoundUBO) {
            GL_ERROR_CHECK("UBO", "updateBuffer", "Prexisting");
            VERIFY_BOUND_UBO(expectedBoundUBO, "updateBuffer");

            glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);

            GL_ERROR_CHECK("UBO", "updateBuffer", "glBufferSubData");
        }

        void bindBufferBase(GLuint bindingPoint, GLuint UBO) {
            GL_ERROR_CHECK("UBO", "bindBufferBase", "Prexisting");

            glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, UBO);

            GL_ERROR_CHECK("UBO", "bindBufferBase", "glBindBufferBase");
        }
    }
}
#include "glh/UBO.h"

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

#define VERIFY_BOUND_UBO(expectedBoundUBO, funcName)                                       \
do {                                                                                       \
    if (expectedBoundUBO == 0) continue;                                                   \
    if (expectedBoundUBO != debugInfoUBO->currentlyBoundUBO) {                             \
        std::cerr << "glh::UBO::" << funcName << "()"                                     \
            << " UBO expected=" <<  expectedBoundUBO                                       \
            << " UBO current=" << debugInfoUBO->currentlyBoundUBO << '\n';                 \
    }                                                                                      \
} while(0)

#define TRACK_BOUND_UBO(newUBO) debugInfoUBO->currentlyBoundUBO = newUBO

#else

#define VERIFY_BOUND_UBO(expectedBoundUBO, funcName)
#define TRACK_BOUND_UBO(newUBO)

#endif

namespace glh {
    namespace UBO {
        void create(GLuint& UBO) {
            glGenBuffers(1, &UBO);
        }

        void create(GLsizei num, GLuint* UBOArray) {
            glGenBuffers(num, UBOArray);
        }

        void destroy(GLuint& UBO) {
            glDeleteBuffers(1, &UBO);
        }

        void destroy(GLsizei num, GLuint* UBOArray) {
            glDeleteBuffers(num, UBOArray);
        }

        void bind(GLuint UBO) {
            TRACK_BOUND_UBO(UBO);

            glBindBuffer(GL_UNIFORM_BUFFER, UBO);
        }

        void allocateBuffer(GLsizeiptr size, const void* data, GLenum usage, GLuint expectedBoundUBO) {
            VERIFY_BOUND_UBO(expectedBoundUBO, "allocateBuffer");

            glBufferData(GL_UNIFORM_BUFFER, size, data, usage);
        }

        void updateBuffer(GLintptr offset, GLsizeiptr size, const void* data, GLuint expectedBoundUBO) {
            VERIFY_BOUND_UBO(expectedBoundUBO, "updateBuffer");

            glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
        }

        void bindBufferBase(GLuint bindingPoint, GLuint UBO) {
            glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, UBO);
        }
    }
}
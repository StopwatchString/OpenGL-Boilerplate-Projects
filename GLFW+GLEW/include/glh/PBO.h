#ifndef GLH_PBO_H
#define GLH_PBO_H

#define GLEW_STATIC
#include "GL/glew.h"

#define BUFFER_TARGET 0
namespace glh {
    namespace PBO {

        void create(GLuint& PBO);
        void create(GLsizei num, GLuint* PBOArray);

        void destroy(GLuint& PBO);
        void destroy(GLsizei num, GLuint* PBOArray);

        void bindForUpload(GLuint PBO);
        void bindForDownload(GLuint PBO);

        void allocateBuffer(GLsizeiptr size, const void* data, GLenum usage, GLuint expectedBoundPBO = 0);
        void updateBuffer(GLintptr offset, GLsizeiptr size, const void* data, GLuint expectedBoundPBO = 0);

        void downloadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* data = BUFFER_TARGET);
        void uploadPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data = BUFFER_TARGET);
    }
}

#endif
#ifndef GLH_TEXTURE_H
#define GLH_TEXTURE_H

#define GLEW_STATIC
#include "GL/glew.h"

namespace glh {
    namespace texture {
        void create(GLuint& texture);
        void create(GLsizei num, GLuint* textureArray);

        void destroy(GLuint& texture);
        void destroy(GLsizei num, GLuint* textureArray);

        void bind(GLenum target, GLuint texture);

        void allocateTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLuint expectedBoundTexture = 0);
        void updateTex2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels, GLuint expectedBoundTexture = 0);
    }
}

#endif
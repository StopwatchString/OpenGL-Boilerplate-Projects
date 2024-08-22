#include "glh/Texture.h"
#include "glh/macros.h"

namespace glh {
    namespace texture {
        void create(GLuint& texture) {
            GL_ERROR_CHECK("texture", "create", "Prexisting");

            glGenTextures(1, &texture);
            GL_ERROR_CHECK("texture", "create", "glGenTextures");
        }

        void create(GLsizei num, GLuint* textureArray) {
            GL_ERROR_CHECK("texture", "create", "Prexisting");

            glGenTextures(num, textureArray);
            GL_ERROR_CHECK("texture", "create", "glGenTextures");
        }

        void destroy(GLuint& texture) {
            GL_ERROR_CHECK("texture", "destroy", "Prexisting");

            glDeleteTextures(1, &texture);
            GL_ERROR_CHECK("texture", "destroy", "glDeleteTextures");
        }

        void destroy(GLsizei num, GLuint* textureArray) {
            GL_ERROR_CHECK("texture", "destroy", "Prexisting");

            glDeleteTextures(num, textureArray);
            GL_ERROR_CHECK("texture", "destroy", "glDeleteTextures");
        }

        void bind(GLenum target, GLuint texture) {
            GL_ERROR_CHECK("texture", "bind", "Prexisting");

            glBindTexture(target, texture);
            GL_ERROR_CHECK("texture", "bind", "glBindTexture");
        }

        void allocateTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLuint expectedBoundTexture) {
            GL_ERROR_CHECK("texture", "allocateTexStorage2D", "Prexisting");

            glTexStorage2D(target, levels, internalformat, width, height);
            GL_ERROR_CHECK("texture", "allocateTexStorage2D", "glTexStorage2D");
        }

        void updateTex2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels, GLuint expectedBoundTexture) {
            GL_ERROR_CHECK("texture", "updateTex2D", "Prexisting");

            glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
            GL_ERROR_CHECK("texture", "updateTex2D", "glTexSubImage2D");
        }
    }
}
#include <iostream>

#include "shaders.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "GLClasses/VAO.h"
#include "GLClasses/VBO.h"
#include "GLClasses/ShaderProgram.h"

#include "DebugWindowGLFW.h"

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

typedef struct Vertex
{
    glm::vec2 pos;
    glm::vec3 col;
} Vertex;

Vertex vertices[3] =
{
    { { -0.6f, -0.4f }, { 1.f, 0.f, 0.f } },
    { {  0.6f, -0.4f }, { 0.f, 1.f, 0.f } },
    { {   0.f,  0.6f }, { 0.f, 0.f, 1.f } }
};

int main()
{
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return EXIT_FAILURE;
    }

    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // COMPAT PROFILE CHOSEN

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        glfwTerminate();
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glfwSwapInterval(1);

    // Initialize OpenGL Resources
    VBO vertex_buffer;
    vertex_buffer.bind();
    vertex_buffer.allocate(sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    ShaderProgram program(vertex_shader_text, fragment_shader_text);

    const GLint mvp_location = program.getUniformLocation("MVP");
    const GLint vpos_location = program.getAttribLocation("vPos");
    const GLint vcol_location = program.getAttribLocation("vCol");

    VAO vertex_array;
    vertex_array.bind();

    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void*)offsetof(Vertex, col));

    DebugWindowGLFW debugWindow;

    float r = 1.0f;
    debugWindow.addSliderFloat("r", r, 0.0f, 1.0f);
    float g = 1.0f;
    debugWindow.addSliderFloat("g", g, 0.0f, 1.0f);
    float b = 1.0f;
    debugWindow.addSliderFloat("b", b, 0.0f, 1.0f);
    float a = 1.0f;
    debugWindow.addSliderFloat("a", a, 0.0f, 1.0f);
    debugWindow.addSpacing();

    debugWindow.addSliderFloat("x", vertices[0].pos.x, -1.0f, 1.0f);
    debugWindow.addSliderFloat("y", vertices[0].pos.y, -1.0f, 1.0f);
    debugWindow.addSpacing();

    debugWindow.addSliderFloat("x", vertices[1].pos.x, -1.0f, 1.0f);
    debugWindow.addSliderFloat("y", vertices[1].pos.y, -1.0f, 1.0f);
    debugWindow.addSpacing();

    debugWindow.addSliderFloat("x", vertices[2].pos.x, -1.0f, 1.0f);
    debugWindow.addSliderFloat("y", vertices[2].pos.y, -1.0f, 1.0f);
    debugWindow.addSpacing();

    while (!glfwWindowShouldClose(window)) {

        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);

        program.bind();

        glm::mat4 mvp(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
            );
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&mvp);

        vertex_buffer.bind();
        vertex_buffer.update(0, sizeof(vertices), vertices);

        vertex_array.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        if (debugWindow.isWindowOpen()) {
            debugWindow.draw();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glGetError() != GL_NO_ERROR) {
            std::cout << "GL Error at end of draw" << std::endl;
        }
    }

    glfwTerminate();
    return 0;
}
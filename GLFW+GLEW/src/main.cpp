#include <iostream>

#include "utils.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "GLClasses/VAO.h"
#include "GLClasses/VBO.h"
#include "GLClasses/ShaderProgram.h"
#include "GLClasses/UBO.h"

#include "DebugWindowGLFW.h"

void error_callback(int error, const char* description)
{
    std::cerr << "Error: " << description << '\n';
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

typedef struct Vertex
{
    glm::vec2 position;
    glm::vec3 color;
    glm::vec2 texcoord;
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
        return EXIT_FAILURE;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glfwSwapInterval(1);

    // Initialize OpenGL Resources
    VBO vertex_buffer;
    vertex_buffer.bind();
    vertex_buffer.allocate(sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    ShaderProgram program(loadFile("C:\\dev\\OpenGL-Boilerplate-Projects\\GLFW+GLEW\\res\\default.vert"), loadFile("C:\\dev\\OpenGL-Boilerplate-Projects\\GLFW+GLEW\\res\\default.frag"));

    const GLint vpos_location = program.getAttribLocation("vPos");
    const GLint vcol_location = program.getAttribLocation("vCol");

    VAO vertex_array;
    vertex_array.bind();

    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void*)offsetof(Vertex, color));

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

    debugWindow.addSliderFloat("x", vertices[0].position.x, -1.0f, 1.0f);
    debugWindow.addSliderFloat("y", vertices[0].position.y, -1.0f, 1.0f);
    debugWindow.addSpacing();

    debugWindow.addSliderFloat("x", vertices[1].position.x, -1.0f, 1.0f);
    debugWindow.addSliderFloat("y", vertices[1].position.y, -1.0f, 1.0f);
    debugWindow.addSpacing();

    debugWindow.addSliderFloat("x", vertices[2].position.x, -1.0f, 1.0f);
    debugWindow.addSliderFloat("y", vertices[2].position.y, -1.0f, 1.0f);
    debugWindow.addSpacing();

    program.bind();

    UBO<glm::mat4> mvpUBO(0);
    glm::mat4& mvp = *mvpUBO.data();
    mvp = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    mvpUBO.uploadData();


    while (!glfwWindowShouldClose(window)) {

        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);

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
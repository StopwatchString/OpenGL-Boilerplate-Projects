#include <iostream>

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "GLClasses/VBO.h"
#include "GLClasses/ShaderProgram.h"
#include "GLClasses/UBO.h"
#include "GLClasses/IBO.h"

#include "gltk/VAO.h"

#define DEBUG_WINDOW
#include "DebugWindowGLFW.h"

const std::string vertshader = "res/default.vert";
const std::string fragshader = "res/default.frag";

int windowWidth = 1000;
int windowHeight = 1000;

static glm::mat4 getRotMat(double angleXDeg, double angleYDeg, double angleZDeg)
{
    glm::mat4 rotationMatrix = glm::mat4(1.0f);
    float angleXRad = glm::radians(angleXDeg);
    float angleYRad = glm::radians(angleYDeg);
    float angleZRad = glm::radians(angleZDeg);

    rotationMatrix = glm::rotate(rotationMatrix, angleXRad, glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, angleYRad, glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, angleZRad, glm::vec3(0.0f, 0.0f, 1.0f));

    return rotationMatrix;
}

static void glfw_error_callback(int error, const char* description)
{
    std::cerr << "Error: " << description << '\n';
}

static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

static void glfw_window_size_callback(GLFWwindow* window, int width, int height)
{
    //glViewport(0, 0, width, height); // TODO:: DebugWindow needs a patch to not interrupt outside GLFW callbacks
    windowWidth = width;
    windowHeight = height;
}

struct Vertex
{
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texcoord;
};

std::vector<Vertex> vertices =
{
    { { -0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } }, // Left,  Bottom, Back
    { {  0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } }, // Right, Bottom, Back
    { {  0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } }, // Right, Bottom, Front
    { { -0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } }, // Left,  Bottom, Front
    { { -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } }, // Left,  Top,    Back
    { {  0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } }, // Right, Top,    Back
    { {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } }, // Right, Top,    Front
    { { -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } }, // Left,  Top,    Front
};

// Index data for triangle strip
std::vector<GLuint> indices = {
    0,1,3,2,6,1,5,0,4,3,7,6,4,5
};

struct uniformData {
    glm::mat4 mvp;
    glm::float32_t time;
};

int main()
{
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return EXIT_FAILURE;
    }

    glfwSetErrorCallback(glfw_error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // COMPAT PROFILE CHOSEN

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "OpenGL Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwSetKeyCallback(window, glfw_key_callback);
    glfwSetWindowAspectRatio(window, 1, 1);
    glfwSetWindowSizeCallback(window, glfw_window_size_callback);

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);
    glfwSwapInterval(1);

    glEnable(GL_CULL_FACE);

    // Initialize OpenGL Resources
    ShaderProgram program(vertshader, fragshader);
    if (glGetError() != GL_NO_ERROR) {
        std::cout << "program" << std::endl;
    }

    GLuint vertex_array;
    gltk::VAO::create(vertex_array);
    gltk::VAO::bind(vertex_array);

    VBO vertex_buffer;
    vertex_buffer.allocate(sizeof(Vertex) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

    IBO index_buffer;
    index_buffer.allocate(sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

    gltk::VAO::enableVertexAttribArray(0, vertex_array);
    gltk::VAO::vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void*)offsetof(Vertex, position), vertex_array);
    gltk::VAO::enableVertexAttribArray(1, vertex_array);
    gltk::VAO::vertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void*)offsetof(Vertex, color), vertex_array);
    gltk::VAO::enableVertexAttribArray(2, vertex_array);
    gltk::VAO::vertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void*)offsetof(Vertex, texcoord), vertex_array);

    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;
    float a = 1.0f;
    float xRot = 0.0f;
    float yRot = 0.0f;
    float zRot = 0.0f;
    float xRotSpeed = 0.0f;
    float yRotSpeed = 0.0f;
    float zRotSpeed = 0.0f;
    bool reloadShaders = false;

#ifdef DEBUG_WINDOW
    DebugWindowGLFW debugWindow;
    debugWindow.addSliderFloat("r", r, 0.0f, 1.0f);
    debugWindow.addSliderFloat("g", g, 0.0f, 1.0f);
    debugWindow.addSliderFloat("b", b, 0.0f, 1.0f);
    debugWindow.addSpacing();

    debugWindow.addSliderFloat("xRot Speed", xRotSpeed, 0.0f, 3.0f);
    debugWindow.addSliderFloat("yRot Speed", yRotSpeed, 0.0f, 3.0f);
    debugWindow.addSliderFloat("zRot Speed", zRotSpeed, 0.0f, 3.0f);
    debugWindow.addSpacing();

    for (Vertex& vertex : vertices) {
        debugWindow.addSliderFloat("r", vertex.color.r, 0.0f, 1.0f);
        debugWindow.addSliderFloat("g", vertex.color.g, 0.0f, 1.0f);
        debugWindow.addSliderFloat("b", vertex.color.b, 0.0f, 1.0f);
        debugWindow.addSpacing();
    }

    debugWindow.addButton("Reload Shaders", [&]() {
        reloadShaders = true;
    });
#endif

    UBO<uniformData> ubo(0);
    glm::mat4& mvp = ubo.data()->mvp;
    mvp = getRotMat(0.0, 0.0, 0.0);

    while (!glfwWindowShouldClose(window)) {
#ifdef DEBUG_WINDOW
        if (reloadShaders) {
            program.reloadShaders();
            reloadShaders = false;
        }
        if (debugWindow.isWindowOpen()) {
            debugWindow.draw();
        }
#endif

        glViewport(0, 0, windowWidth, windowHeight);

        program.bind();

        xRot += xRotSpeed;
        yRot += yRotSpeed;
        zRot += zRotSpeed;
        glm::mat4& mvp = ubo.data()->mvp;
        mvp = getRotMat(xRot, yRot, zRot);
        ubo.data()->time = glfwGetTime();
        ubo.uploadData();

        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);

        vertex_buffer.bind();
        vertex_buffer.update(0, sizeof(Vertex) * vertices.size(), vertices.data());

        gltk::VAO::bind(vertex_array);
        glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glGetError() != GL_NO_ERROR) {
            std::cout << "GL Error at end of draw" << std::endl;
        }
    }

    glfwTerminate();
    return 0;
}
#include <iostream>

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glh/VAO.h"
#include "glh/VBO.h"
#include "glh/EBO.h"
#include "glh/UBO.h"
#include "glh/ShaderProgram.h"

#include "utils.h"

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
    GLuint shader_program;
    glh::ShaderProgram::create(shader_program, loadFile(vertshader), loadFile(fragshader));

    GLuint vertex_array;
    glh::VAO::create(vertex_array);
    glh::VAO::bind(vertex_array);

    GLuint vertex_buffer;
    glh::VBO::create(vertex_buffer);
    glh::VBO::bind(vertex_buffer);
    glh::VBO::allocateBuffer(sizeof(Vertex) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW, vertex_buffer);

    GLuint element_buffer;
    glh::EBO::create(element_buffer);
    glh::EBO::bind(element_buffer);
    glh::EBO::allocateBuffer(sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glh::VAO::enableVertexAttribArray(0, vertex_array);
    glh::VAO::vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void*)offsetof(Vertex, position), vertex_array);
    glh::VAO::enableVertexAttribArray(1, vertex_array);
    glh::VAO::vertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void*)offsetof(Vertex, color), vertex_array);
    glh::VAO::enableVertexAttribArray(2, vertex_array);
    glh::VAO::vertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
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

    uniformData data;
    data.mvp = getRotMat(0.0f, 0.0f, 0.0f);

    GLuint uniform_buffer;
    glh::UBO::create(uniform_buffer);
    glh::UBO::bind(uniform_buffer);
    glh::UBO::allocateBuffer(sizeof(data), &data, GL_DYNAMIC_DRAW, uniform_buffer);
    glh::UBO::bindBufferBase(0, uniform_buffer);

    while (!glfwWindowShouldClose(window)) {
#ifdef DEBUG_WINDOW
        if (reloadShaders) {
            // impl later
            reloadShaders = false;
        }
        if (debugWindow.isWindowOpen()) {
            debugWindow.draw();
        }
#endif

        glViewport(0, 0, windowWidth, windowHeight);

        glh::ShaderProgram::bind(shader_program);

        xRot += xRotSpeed;
        yRot += yRotSpeed;
        zRot += zRotSpeed;
        data.mvp = getRotMat(xRot, yRot, zRot);
        data.time = glfwGetTime();
        
        glh::UBO::updateBuffer(0, sizeof(uniformData), &data, uniform_buffer);

        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);

        glh::VBO::bind(vertex_buffer);
        glh::VBO::updateBuffer(0, sizeof(Vertex) * vertices.size(), vertices.data(), vertex_buffer);

        glh::VAO::bind(vertex_array);
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
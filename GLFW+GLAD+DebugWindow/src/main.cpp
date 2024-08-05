#include <iostream>

#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "DebugWindow.h"

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

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
    gladLoadGL(glfwGetProcAddress);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glfwSwapInterval(1);

    // DebugWindow
    DebugWindow dw;
    float r = 0.65f;
    dw.addSliderFloat("r", r, 0.0f, 1.0f);
    float g = 0.25f;
    dw.addSliderFloat("g", g, 0.0f, 1.0f);
    float b = 0.5f;
    dw.addSliderFloat("b", b, 0.0f, 1.0f);
    float a = 1.0f;
    dw.addSliderFloat("a", a, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {

        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
        
        dw.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
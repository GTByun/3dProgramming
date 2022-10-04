#include <GLFW/glfw3.h>
#pragma comment(lib, "OpenGL32")
#include <glm/glm.hpp>

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS && key == GLFW_KEY_SPACE)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 640, "title", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glClearColor(0.5, 0.5, 0.5, 1);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1, 1, 1);
        glVertex2f(0, 0);
        double stack = 3.141592 / 180;
        double stacker = 0;
        for (size_t i = 0; i < 361; i++)
        {
            glVertex2f(glm::cos(stacker), glm::sin(stacker));
            stacker += stack;
        }
        glEnd();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
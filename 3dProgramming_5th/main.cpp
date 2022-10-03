#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdlib.h>
#include <time.h>
#include "object.hpp"


#pragma comment(lib, "OpenGL32")


GLFWwindow* window;
FireBall* f;

void Init();
void Update();
void Release();

static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(void);

float setRand()
{
    return (rand() % 10000 + 1) / 10000.0f;
}


void Init()
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    f = new FireBall();
}

void Release()
{
    delete(f);

    glfwDestroyWindow(window);
    glfwTerminate();
}
void Update()
{
    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        ////90도와 같이 각도로 연산하고 싶으면
        ////glm의 삼각함수는 radian 형식으로 입력을 받기 때문에 변환해서 넣어주어야한다.
        //glm::sin(glm::radians(90.0));  

        glClearColor(.0f, 0.0f, 0.0f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);

        

        glLineWidth(7.0f);
        float x, y, z;
        glBegin(GL_LINE_LOOP);
        for (float theta = 0; theta < 360; theta++)
        {
            x = glm::sin(glm::radians(theta)) * 0.5;
            y = glm::cos(glm::radians(theta)) * 0.2 - 0.6f;
            z = glm::cos(glm::radians(theta)) * 0.5;
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            glVertex3f(x, y, z);
        }
        glEnd();

        glBegin(GL_LINE_LOOP);
        float theta = 0;
        for (size_t i = 0; i < 5; i++)
        {
            x = glm::sin(glm::radians(theta)) * 0.5;
            y = glm::cos(glm::radians(theta)) * 0.2 - 0.6f;
            z = glm::cos(glm::radians(theta)) * 0.5;
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            glVertex3f(x, y, z);
            theta += 144;
        }
        glEnd();

        float tower = 0.2f;

        srand(time(NULL));
        glBegin(GL_LINE_STRIP);
        float x1, x2, x3;
        float y1, y2, y3;
        float z1, z2, z3;
        glColor4f(setRand(), setRand(), setRand(), setRand() * 0.5f);
        glVertex3f(0.0f, -0.1f, 0.5f);
        for (size_t height = 0; height < 6; height++)
        {
            float high = tower * height - 0.6f;
            for (float i = -45; i < 45; i++)
            {
                x1 = glm::sin(glm::radians(i * 2)) * 0.5;
                x2 = glm::sin(glm::radians(i * 2 + 1)) * 0.5;
                x3 = glm::sin(glm::radians(i * 2 + 2)) * 0.5;
                y1 = glm::cos(glm::radians(i * 2)) * 0.2 + high;
                y2 = glm::cos(glm::radians(i * 2 + 1)) * 0.2 + high;
                y3 = glm::cos(glm::radians(i * 2 + 2)) * 0.2 + high;
                z1 = glm::cos(glm::radians(i * 2)) * 0.5;
                z2 = glm::cos(glm::radians(i * 2 + 1)) * 0.5;
                z3 = glm::cos(glm::radians(i * 2 + 2)) * 0.5;
                glColor4f(setRand(), setRand(), setRand(), setRand() * 0.5f);
                glVertex3f(x2, y2, z2);
                glColor4f(setRand(), setRand(), setRand(), setRand() * 0.5f);
                glVertex3f(x1, y1 + tower, z1);
                glColor4f(setRand(), setRand(), setRand(), setRand() * 0.5f);
                glVertex3f(x2, y2 + tower, z2);
                glColor4f(setRand(), setRand(), setRand(), setRand() * 0.5f);
                glVertex3f(x2, y2 + tower, z2);
                glColor4f(setRand(), setRand(), setRand(), setRand() * 0.5f);
                glVertex3f(x3, y3 + tower, z3);
                glColor4f(setRand(), setRand(), setRand(), setRand() * 0.5f);
                glVertex3f(x2, y2, z2);
                glColor4f(setRand(), setRand(), setRand(), setRand() * 0.5f);
                glVertex3f(x3, y3, z3);
            }
        }
        glEnd();
        f->draw();
        glBegin(GL_LINE_STRIP);
        glColor4f(setRand(), setRand(), setRand(), setRand() * 0.5f);
        glVertex3f(0.5f, -0.6f, 0.0f);
        for (size_t height = 0; height < 6; height++)
        {
            float high = tower * height - 0.6f;
            for (float i = 45; i < 135; i++)
            {
                x1 = glm::sin(glm::radians(i * 2)) * 0.5;
                x2 = glm::sin(glm::radians(i * 2 + 1)) * 0.5;
                x3 = glm::sin(glm::radians(i * 2 + 2)) * 0.5;
                y1 = glm::cos(glm::radians(i * 2)) * 0.2 + high;
                y2 = glm::cos(glm::radians(i * 2 + 1)) * 0.2 + high;
                y3 = glm::cos(glm::radians(i * 2 + 2)) * 0.2 + high;
                z1 = glm::cos(glm::radians(i * 2)) * 0.5;
                z2 = glm::cos(glm::radians(i * 2 + 1)) * 0.5;
                z3 = glm::cos(glm::radians(i * 2 + 2)) * 0.5;
                glColor4f(setRand(), setRand(), setRand(), setRand() * 0.5f);
                glVertex3f(x2, y2, z2);
                glColor4f(setRand(), setRand(), setRand(), setRand() * 0.5f);
                glVertex3f(x1, y1 + tower, z1);
                glColor4f(setRand(), setRand(), setRand(), setRand() * 0.5f);
                glVertex3f(x2, y2 + tower, z2);
                glColor4f(setRand(), setRand(), setRand(), setRand() * 0.5f);
                glVertex3f(x2, y2 + tower, z2);
                glColor4f(setRand(), setRand(), setRand(), setRand() * 0.5f);
                glVertex3f(x3, y3 + tower, z3);
                glColor4f(setRand(), setRand(), setRand(), setRand() * 0.5f);
                glVertex3f(x2, y2, z2);
                glColor4f(setRand(), setRand(), setRand(), setRand() * 0.5f);
                glVertex3f(x3, y3, z3);
            }
        }
        glEnd();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void)
{
    Init();
    Update();
    Release();

    exit(EXIT_SUCCESS);
}